"""Guest image abstraction for the lifter: a PE file or a raw flat blob."""
import struct


class Section:
    __slots__ = ("name", "va", "vsize", "rawsize", "flags")

    def __init__(self, name, va, vsize, rawsize, flags):
        self.name, self.va, self.vsize, self.rawsize, self.flags = name, va, vsize, rawsize, flags


class Image:
    """A guest image mapped at `base`; `text` is the [start, end) VA range holding code."""

    def __init__(self, base, data, text_start, text_end, entry, sections, imports):
        self.base = base
        self.data = data
        self.text_start = text_start
        self.text_end = text_end
        self.entry = entry
        self.sections = sections
        self.imports = imports  # list of (iat_va, dll, name)
        self.end = base + len(data)

    @classmethod
    def from_pe(cls, path):
        import pefile

        pe = pefile.PE(path)
        base = pe.OPTIONAL_HEADER.ImageBase
        data = bytes(pe.get_memory_mapped_image())
        sections = []
        text = None
        for s in pe.sections:
            name = s.Name.rstrip(b"\0").decode("latin1")
            sec = Section(name, base + s.VirtualAddress, s.Misc_VirtualSize, s.SizeOfRawData, s.Characteristics)
            sections.append(sec)
            if text is None and (s.Characteristics & 0x20):  # IMAGE_SCN_CNT_CODE
                text = sec
        if text is None:
            raise SystemExit("no code section in PE")
        imports = []
        for e in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
            dll = e.dll.decode("latin1").lower()
            for i in e.imports:
                name = i.name.decode("latin1") if i.name else "ord%d" % i.ordinal
                imports.append((i.address, dll, name))
        entry = base + pe.OPTIONAL_HEADER.AddressOfEntryPoint
        return cls(base, data, text.va, text.va + text.vsize, entry, sections, imports)

    @classmethod
    def from_raw(cls, path, base):
        data = open(path, "rb").read()
        sec = Section(".text", base, len(data), len(data), 0x60000020)
        return cls(base, data, base, base + len(data), base, [sec], [])

    def in_text(self, a):
        return self.text_start <= a < self.text_end

    def has(self, a, n=1):
        return self.base <= a and a + n <= self.end

    def u8(self, a):
        return self.data[a - self.base]

    def u32(self, a):
        return struct.unpack_from("<I", self.data, a - self.base)[0]

    def bytes_at(self, a, n):
        o = a - self.base
        return self.data[o : o + n]
