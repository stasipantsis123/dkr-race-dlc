"""Check actual linked MIPS function stack adjustments, not host C behavior.

The runtime enters the mod on a 16-byte-aligned owned stack. Every fixed
SP adjustment must preserve it so native SDK calls remain admissible.
"""
from pathlib import Path
import argparse
import struct

parser = argparse.ArgumentParser()
parser.add_argument('elf', type=Path)
args = parser.parse_args()
data = args.elf.read_bytes()
assert data[:7] == b'\x7fELF\x01\x02\x01'
h = struct.unpack_from('>HHIIIIIHHHHHH', data, 16)
assert h[1] == 8, 'expected MIPS ELF'
sections = [struct.unpack_from('>10I', data, h[5]+i*h[10]) for i in range(h[11])]
functions = []
for section in sections:
    if section[1] != 2:
        continue
    names = sections[section[6]]
    strings = data[names[4]:names[4]+names[5]]
    for pos in range(section[4], section[4]+section[5], 16):
        name, value, size, info, other, index = struct.unpack_from('>IIIBBH', data, pos)
        if not value or not size or info & 15 != 2:
            continue
        owner = sections[index]
        assert owner[3] <= value and value + size <= owner[3]+owner[5]
        start = owner[4]+value-owner[3]
        text = strings[name:].split(b'\0', 1)[0].decode()
        functions.append((text, value, data[start:start+size]))
assert functions
adjustments = []
for name, address, code in functions:
    assert len(code) % 4 == 0
    for offset in range(0, len(code), 4):
        word = struct.unpack_from('>I', code, offset)[0]
        if word & 0xffff0000 == 0x27bd0000:  # addiu sp, sp, signed immediate
            value = struct.unpack('>h', struct.pack('>H', word & 0xffff))[0]
            assert value % 16 == 0, f'{name}+0x{offset:x}: SP adjustment {value} breaks native-call alignment'
            adjustments.append((name, value))
assert adjustments
print(f'PASS: {len(functions)} actual MIPS functions, {len(adjustments)} fixed SP adjustments all preserve 16-byte alignment')
