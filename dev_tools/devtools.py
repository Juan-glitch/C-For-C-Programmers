#!/usr/bin/env python3
"""Project devtools wrapper for C-For-C-Programmers."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path


def _repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def _normalize(args: list[str]) -> list[str]:
    return args[1:] if args and args[0] == "--" else args


class DevToolsCli:
    def build_parser(self) -> argparse.ArgumentParser:
        parser = argparse.ArgumentParser(prog="devtools", description="C-For-C-Programmers dev_tools CLI")
        subcommands = parser.add_subparsers(dest="command", required=True)

        lab = subcommands.add_parser("lab", add_help=False, help="Human Plugin OS lab probes")
        lab.add_argument("args", nargs=argparse.REMAINDER)
        lab.set_defaults(func=self.run_lab)

        tools = subcommands.add_parser("tools", add_help=False, help="Human Plugin OS tool registry")
        tools.add_argument("args", nargs=argparse.REMAINDER)
        tools.set_defaults(func=self.run_tools)
        return parser

    def run_lab(self, args: argparse.Namespace) -> int:
        import lab_cli

        return lab_cli.main(_normalize(args.args))

    def run_tools(self, args: argparse.Namespace) -> int:
        from devtools_core import tools as core_tools

        return core_tools.main(_normalize(args.args), default_root=_repo_root())

    def main(self, argv: list[str] | None = None) -> int:
        argv = list(sys.argv[1:] if argv is None else argv)
        if argv and argv[0] == "lab":
            return self.run_lab(argparse.Namespace(args=argv[1:]))
        if argv and argv[0] == "tools":
            return self.run_tools(argparse.Namespace(args=argv[1:]))
        parser = self.build_parser()
        args = parser.parse_args(argv)
        return int(args.func(args))


def main(argv: list[str] | None = None) -> int:
    return DevToolsCli().main(argv)


if __name__ == "__main__":
    raise SystemExit(main())
