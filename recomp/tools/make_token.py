#!/usr/bin/env python3
"""Build the session token the game expects as its whole command line.

  make_token.py USER [PASSWORD] [--launcher orig/Launcher.cs]

The game exits at once unless GetCommandLineA() is exactly 96 characters: the
hexadecimal form of three AES-128-ECB blocks, as its launcher produces them
(user name, password and a zero block, each padded with zeros to 16 bytes).
The launcher in orig/ uses the user name for both of the first two blocks,
which is the default here. The key is read from the launcher's source so that
it does not have to be stored in this repository.

Pass the result to the recompiled game with  --cmdline TOKEN.
"""
import argparse
import os
import re
import subprocess
import sys


def read_key(path):
    text = open(path, encoding="utf-8", errors="replace").read()
    m = re.search(r"byte\[\]\s+key\s*=\s*\{([^}]*)\}", text)
    if not m:
        sys.exit("%s: no `byte[] key = {...}` found" % path)
    key = bytes(int(x, 16) for x in re.findall(r"0x([0-9A-Fa-f]{1,2})", m.group(1)))
    if len(key) != 16:
        sys.exit("%s: the key is %d bytes, expected 16" % (path, len(key)))
    return key


def encrypt_block(key, block):
    try:
        from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
    except ImportError:
        out = subprocess.run(["openssl", "enc", "-aes-128-ecb", "-nopad", "-K", key.hex()], input=block,
                             stdout=subprocess.PIPE, check=True).stdout
        return out
    enc = Cipher(algorithms.AES(key), modes.ECB()).encryptor()
    return enc.update(block) + enc.finalize()


def pad16(s):
    b = s.encode("ascii")
    if len(b) > 16:
        sys.exit("%r is longer than 16 characters" % s)
    return b + bytes(16 - len(b))


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("user")
    ap.add_argument("password", nargs="?")
    ap.add_argument("--launcher", default=os.path.join(here, "..", "..", "orig", "Launcher.cs"))
    args = ap.parse_args()
    key = read_key(args.launcher)
    blocks = [pad16(args.user), pad16(args.password if args.password is not None else args.user), bytes(16)]
    print("".join(encrypt_block(key, b).hex().upper() for b in blocks))


if __name__ == "__main__":
    main()
