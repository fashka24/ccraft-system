# automatic installation

import os, shutil

n = os.name == "nt"

EXECUTABLE_FILE_EXT = ".exe" if n else ""

EXECUTABLE_FILE_PATH = "bin/ccraft" + EXECUTABLE_FILE_EXT
EXECUTABLE_FILE_ONLY_PATH = "ccraft" + EXECUTABLE_FILE_EXT

if not os.access(EXECUTABLE_FILE_PATH, os.F_OK):
    print("[info] compiling main project")
    
    os.system("python build.py")

print()

if n:
    files_to_copy = {
        EXECUTABLE_FILE_PATH: EXECUTABLE_FILE_ONLY_PATH,
        "include\\CcraftAPI.hpp": "include\\CcraftAPI.hpp",
    }

    print("[info] start copying files")
    os.makedirs("C:\\Ccraft\\include", exist_ok=True)

    for file_to_copy, path_to_copy in files_to_copy.items():
        print(f"[info] copying {file_to_copy} to C:\\Ccraft\\{path_to_copy}")
        shutil.copy2(file_to_copy, f"C:\\Ccraft\\{path_to_copy}")
else:
    files_to_copy = {
        EXECUTABLE_FILE_PATH: EXECUTABLE_FILE_ONLY_PATH,
        "include/CcraftAPI.hpp": "include/CcraftAPI.hpp",
    }

    print("[info] start copying files")
    os.makedirs("/usr/ccraft/include", exist_ok=True)

    for file_to_copy, path_to_copy in files_to_copy.items():
        print(f"[info] copying {file_to_copy} to /usr/ccraft/{path_to_copy}")
        shutil.copy2(file_to_copy, f"/usr/ccraft/{path_to_copy}")

print("\n[success] installation finished")