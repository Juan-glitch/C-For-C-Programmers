#!/usr/bin/env python3
"""Small Python probe template."""

from __future__ import annotations


def compute(value: int) -> int:
    """Replace this tiny function with the piece you want to test."""
    return value * 2


def main() -> int:
    result = compute(21)
    print("result=", result)
    return 0 if result == 42 else 1


if __name__ == "__main__":
    raise SystemExit(main())
