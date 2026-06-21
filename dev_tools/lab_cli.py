#!/usr/bin/env python3
"""Project wrapper for the common Human Plugin OS Lab CLI."""

from __future__ import annotations

from pathlib import Path
from typing import Sequence

from devtools_core.lab import main as core_lab_main


def _default_repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def main(argv: Sequence[str] | None = None) -> int:
    return core_lab_main(argv, default_root=_default_repo_root())


if __name__ == "__main__":
    raise SystemExit(main())
