#!/usr/bin/env python3
"""Autocontained C++ probe build helper.

Tries CMake first; falls back to g++ so the probe compiles even when cmake
is not installed in the container.
"""

from __future__ import annotations

import os
import shutil
import subprocess
import sys
from pathlib import Path


BUILD_DIR = Path(".generated/build")
EXE_NAME: str = "{{exe_name}}"
CXX_STANDARD = "17"


def run(argv: list[str]) -> int:
    print("$", " ".join(argv))
    return subprocess.run(argv, text=True).returncode


def cmake_available() -> bool:
    return shutil.which("cmake") is not None


def configure() -> int:
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    if cmake_available():
        return run(["cmake", "-S", ".", "-B", str(BUILD_DIR), "-DCMAKE_BUILD_TYPE=Debug"])
    print("[INFO] cmake not found; using g++ fallback for configuration")
    return 0


def compile_sources() -> int:
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    if cmake_available():
        return run(["cmake", "--build", str(BUILD_DIR)])

    # Fallback direct g++ compilation.
    cxx = os.environ.get("CXX", "g++")
    flags = [f"-std=c++{CXX_STANDARD}", "-O0", "-g", "-Wall", "-Wextra"]
    rc = run([cxx, *flags, "main.cpp", "-o", str(BUILD_DIR / EXE_NAME)])
    if rc != 0:
        return rc
    return run([cxx, *flags, "tests/test_main.cpp", "-o", str(BUILD_DIR / f"{EXE_NAME}_tests")])


def main() -> int:
    if len(sys.argv) < 2:
        print("usage: lab_build.py {configure|compile|build}", file=sys.stderr)
        return 2
    cmd = sys.argv[1]
    if cmd == "configure":
        return configure()
    if cmd == "compile":
        return compile_sources()
    if cmd == "build":
        rc = configure()
        if rc != 0:
            return rc
        return compile_sources()
    print(f"unknown command: {cmd}", file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
