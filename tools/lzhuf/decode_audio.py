"""
Extract audio from GunBound's sound.xfs to standard playable files.

sound.xfs holds two audio types, both stored RAW (mode flag 1, no LZHUF):

  - .xes (85 files): sound effects. Confirmed format = a "headerless WAV":
    a 16-byte block matching a standard WAV `fmt ` chunk's fields
        u16 audioFormat  (1 = PCM)
        u16 numChannels  (2)
        u32 sampleRate   (22050)
        u32 byteRate     (88200 = 22050*2*2)
        u16 blockAlign   (4 = 2ch * 2 bytes)
        u16 bitsPerSample(16)
    followed immediately by raw little-endian signed 16-bit PCM samples.
    All 85 .xes files in the shipped sound.xfs use the identical format
    above. Converting to a real .wav is just prepending a RIFF/WAVE header
    around the existing fmt fields + PCM data (Python's `wave` module does
    this for us).

  - .mp3 (11 files): music tracks. Already standard MPEG audio (valid frame
    sync / ID3), written out byte-for-byte, directly playable.

Usage:
    python3 decode_audio.py /path/to/sound.xfs /path/to/output_dir
"""
import os
import struct
import sys
import wave

from extract_toc import read_toc


def read_raw_entry(xfs_path, mode_flag, file_offset, decompressed_size, compressed_size):
    # sound.xfs entries are all mode_flag == 1 (raw); handle the compressed
    # case too for completeness.
    with open(xfs_path, 'rb') as f:
        if mode_flag == 1:
            f.seek(file_offset)
            return f.read(decompressed_size)
        from lzhuf import decode_lzhuf
        f.seek(file_offset)
        real_compressed_size, checksum = struct.unpack('<II', f.read(8))
        cdata = f.read(real_compressed_size)
        return decode_lzhuf(cdata, decompressed_size)


def xes_to_wav(xes_bytes, out_path):
    audio_fmt, channels, sample_rate, byte_rate, block_align, bits = struct.unpack('<HHIIHH', xes_bytes[:16])
    if audio_fmt != 1:
        raise ValueError(f'unexpected audioFormat {audio_fmt} (only PCM=1 handled)')
    pcm = xes_bytes[16:]
    with wave.open(out_path, 'wb') as w:
        w.setnchannels(channels)
        w.setsampwidth(bits // 8)
        w.setframerate(sample_rate)
        w.writeframes(pcm)
    return channels, sample_rate, bits, len(pcm) / byte_rate


def main():
    if len(sys.argv) != 3:
        print(f'usage: {sys.argv[0]} <sound.xfs> <output_dir>')
        sys.exit(1)
    xfs_path, out_dir = sys.argv[1:3]
    os.makedirs(out_dir, exist_ok=True)
    entries, _, _, _ = read_toc(xfs_path)

    n_wav = n_mp3 = n_other = 0
    for name, mode_flag, file_offset, decompressed_size, compressed_size in entries:
        data = read_raw_entry(xfs_path, mode_flag, file_offset, decompressed_size, compressed_size)
        low = name.lower()
        safe = name.replace('/', '_').replace('\\', '_')
        if low.endswith('.xes'):
            out_path = os.path.join(out_dir, safe[:-4] + '.wav')
            xes_to_wav(data, out_path)
            n_wav += 1
        elif low.endswith('.mp3'):
            out_path = os.path.join(out_dir, safe)
            with open(out_path, 'wb') as f:
                f.write(data)
            n_mp3 += 1
        else:
            out_path = os.path.join(out_dir, safe)
            with open(out_path, 'wb') as f:
                f.write(data)
            n_other += 1
    print(f'DONE: {n_wav} .xes -> .wav, {n_mp3} .mp3 copied, {n_other} other')


if __name__ == '__main__':
    main()
