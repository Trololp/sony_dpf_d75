import struct
import lzo

input_file = "archive.lzo"
output_file = "firmware.bin"

with open(input_file, "rb") as f:
    # Read and parse header
    header = f.read(16)
    if len(header) < 16:
        raise ValueError("File too small to contain valid header")

    signature, unk, out_len, source_len = struct.unpack("<4sIII", header)

    if signature != b"LZO\0":
        raise ValueError(f"Invalid signature: {signature}")

    print(f"Signature : {signature}")
    print(f"Unknown   : {unk}")
    print(f"Out length: {out_len}")
    print(f"Src length: {source_len}")

    # Read compressed data
    compressed = f.read(source_len)
    if len(compressed) != source_len:
        raise ValueError("Compressed stream size mismatch")

# Decompress
decompressed = lzo.decompress(compressed, False, out_len)

if len(decompressed) != out_len:
    raise ValueError(
        f"Decompressed size mismatch: expected {out_len}, got {len(decompressed)}"
    )

# Save to file
with open(output_file, "wb") as f:
    f.write(decompressed)

print(f"Decompressed {len(decompressed)} bytes to {output_file}")
