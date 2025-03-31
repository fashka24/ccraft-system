import os

COMPILER = "clang++"

TARGET_FILE = "ccraft.cpp"
OUTPUT_FILE = "bin/ccraft" + \
    ".exe" if os.name == "nt" else ""

OPTIMIZATION = "-O3"
FLAGS = [
    "-ffast-math", "-w", "-std=c++20"
]

print(f"[COMPILATION] {COMPILER} {" ".join(FLAGS)} {TARGET_FILE} -o {OUTPUT_FILE} {OPTIMIZATION}")
os.system(f"{COMPILER} {" ".join(FLAGS)} {TARGET_FILE} -o {OUTPUT_FILE} {OPTIMIZATION}")