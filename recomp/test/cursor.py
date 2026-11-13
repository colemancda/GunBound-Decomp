#!/usr/bin/env python3
"""Where two frame dumps of the game differ.

  cursor.py A.png B.png X Y [RADIUS]

Used by pad.sh: A is a frame from a run without input, B the same frame from a
run in which the pointer was moved to (X, Y). The only thing that may differ is
the cursor the game draws, so B must differ from A near (X, Y) and nowhere far
from both (X, Y) and the place the cursor is in A. Exit status 0 if so.

  cursor.py --red FILE X0 Y0 X1 Y1

prints the number of saturated red pixels in a rectangle of a frame (the
battle's power bar; used by online.sh).

Reads the uncompressed 8-bit RGB PNG files the runtime writes (and any other
non-interlaced 8-bit RGB PNG).
"""
import struct
import sys
import zlib


def read_png(path):
    data = open(path, "rb").read()
    assert data[:8] == b"\x89PNG\r\n\x1a\n", path
    pos, idat, width, height = 8, b"", 0, 0
    while pos < len(data):
        n, kind = struct.unpack(">I4s", data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + n]
        if kind == b"IHDR":
            width, height, depth, colour = struct.unpack(">IIBB", body[:10])
            assert depth == 8 and colour == 2, "8-bit RGB expected"
        elif kind == b"IDAT":
            idat += body
        pos += 12 + n
    raw = zlib.decompress(idat)
    stride = width * 3 + 1
    rows = []
    for y in range(height):
        assert raw[y * stride] == 0, "unfiltered rows expected"
        rows.append(raw[y * stride + 1:(y + 1) * stride])
    return width, height, rows


def main():
    if sys.argv[1] == "--red":
        _, _, rows = read_png(sys.argv[2])
        x0, y0, x1, y1 = map(int, sys.argv[3:7])
        n = 0
        for row in rows[y0:y1]:
            for col in range(x0, x1):
                r, g, b = row[3 * col:3 * col + 3]
                n += r > 200 and g < 60 and b < 60
        print(n)
        return
    a, b = read_png(sys.argv[1]), read_png(sys.argv[2])
    x, y = int(sys.argv[3]), int(sys.argv[4])
    radius = int(sys.argv[5]) if len(sys.argv) > 5 else 40
    assert a[:2] == b[:2], "frames differ in size"
    width, height = a[:2]
    near = far = 0
    box = None
    for row in range(height):
        ra, rb = a[2][row], b[2][row]
        if ra == rb:
            continue
        for col in range(width):
            if ra[3 * col:3 * col + 3] != rb[3 * col:3 * col + 3]:
                if abs(col - x) <= radius and abs(row - y) <= radius:
                    near += 1
                else:
                    far += 1
                    box = (col, row, col, row) if box is None else (
                        min(box[0], col), min(box[1], row), max(box[2], col), max(box[3], row))
    # away from the pointer only the cursor's old place may differ: a small patch
    old_ok = box is None or (box[2] - box[0] <= 2 * radius and box[3] - box[1] <= 2 * radius)
    print("%d pixels differ near (%d, %d), %d elsewhere%s" % (
        near, x, y, far, "" if box is None else " within %d,%d-%d,%d" % box))
    sys.exit(0 if near >= 20 and old_ok else 1)


if __name__ == "__main__":
    main()
