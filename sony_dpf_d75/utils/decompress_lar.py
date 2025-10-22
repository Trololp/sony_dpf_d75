import struct
import lzo

import sys


input_file = "spmm.lar"
output_file = "spmm_decompressed.lar"

with open(input_file, "rb") as f:
    # Read and parse header
    header = f.read(16)

    signature, decomp_size, entries_count, blk_sz, sz_table = struct.unpack("<4sIHHI", header)

    if signature != b"\xd0\x0b\x82\xfa":
        raise ValueError(f"Invalid signature: {signature}")


    table = []

    for i in range(entries_count):
        table.append(struct.unpack("<I", f.read(4))[0])


    print(table)

    for i in range(entries_count - 1):
        if(table[i + 1] - table[i] > blk_sz):
            print("shi.......!!!!!")
            sys.exit()

    decompressed_data = b"";

    for i in range(entries_count - 1):
        f.seek(table[i], 0)
        if (table[i + 1] - table[i] == blk_sz):
            decompressed_data = decompressed_data + f.read(blk_sz)
            continue
        compressed = f.read(table[i + 1] - table[i])
        decompressed = lzo.decompress(compressed, False, blk_sz)
        decompressed_data = decompressed_data + decompressed




# Save to file
with open(output_file, "wb") as f:
    f.write(decompressed_data)

print(f"Decompressed {len(decompressed_data)} bytes to {output_file}")

