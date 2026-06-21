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
from typing import List, Tuple


BUILD_DIR = Path(".generated/build")
EXE_NAME: str = "mst-kruskal-step"
CXX_STANDARD = "17"
ASSIGN_INCLUDE = "-I../../../src/Module 4/Assignment4_MST"
SOURCES = [
    "../../../src/Module 4/Assignment4_MST/Graph.cpp",
    "../../../src/Module 4/Assignment4_MST/utils/DisjointSet.cpp",
]


def run(argv: list[str]) -> int:
    print("$", " ".join(argv))
    return subprocess.run(argv, text=True).returncode


def cmake_available() -> bool:
    return shutil.which("cmake") is not None


def discover_subtests() -> List[Tuple[str, Path]]:
    tests_dir = Path("test")
    subtests: List[Tuple[str, Path]] = []
    if tests_dir.exists():
        for path in sorted(tests_dir.glob("test_*.cpp")):
            name = path.stem[len("test_"):]
            subtests.append((name, path))
    return subtests


def configure() -> int:
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    if cmake_available():
        return run(["cmake", "-S", ".", "-B", str(BUILD_DIR), "-DCMAKE_BUILD_TYPE=Debug"])
    print("[INFO] cmake not found; using g++ fallback for configuration")
    return 0


def compile_sources() -> int:
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    subtests = discover_subtests()

    if cmake_available():
        return run(["cmake", "--build", str(BUILD_DIR)])

    # Fallback direct g++ compilation.
    cxx = os.environ.get("CXX", "g++")
    flags = [f"-std=c++{CXX_STANDARD}", "-O0", "-g", "-Wall", "-Wextra"]

    failed = 0
    for sub_name, sub_path in subtests:
        out = BUILD_DIR / f"{EXE_NAME}_{sub_name}"
        rc = run([cxx, *flags, ASSIGN_INCLUDE, str(sub_path), *SOURCES, "-o", str(out)])
        if rc != 0:
            failed += 1

    # Combined runner for all subtests.
    main_out = BUILD_DIR / EXE_NAME
    rc = run([cxx, *flags, ASSIGN_INCLUDE, "main.cpp", *SOURCES, "-o", str(main_out)])
    if rc != 0:
        failed += 1

    return 1 if failed else 0


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
