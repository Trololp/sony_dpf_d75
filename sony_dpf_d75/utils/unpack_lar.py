import os
import struct

ENTRY_SIZE = 64

# Table entry format:
# int file_offset, int data_size, int unk, int unk2, char file_path[48]
ENTRY_STRUCT = struct.Struct("<iiii48s")


def unpack_archive(archive_path, output_dir):
    with open(archive_path, "rb") as f:
        while True:
            data = f.read(ENTRY_SIZE)
            if len(data) < ENTRY_SIZE:
                break  # unexpected EOF

            file_offset, data_size, unk, unk2, raw_path = ENTRY_STRUCT.unpack(data)

            # Check for empty entry (all zeros)
            if file_offset == 0 and data_size == 0 and unk == 0 and unk2 == 0 and raw_path.strip(b"\x00") == b"":
                break

            # Decode file path (strip null terminator)
            file_path = raw_path.split(b"\x00", 1)[0].decode("utf-8", errors="ignore")

            # Read file data
            cur_pos = f.tell()
            f.seek(file_offset)
            file_data = f.read(data_size)
            f.seek(cur_pos)

            # Prepare output path
            out_path = os.path.join(output_dir, file_path.replace("\\", os.sep))
            os.makedirs(os.path.dirname(out_path), exist_ok=True)

            # Write file
            with open(out_path, "wb") as out_f:
                out_f.write(file_data)

            print(f"Extracted: {file_path} -> {out_path}")


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <archive_file> <output_dir>")
        sys.exit(1)

    unpack_archive(sys.argv[1], sys.argv[2])
