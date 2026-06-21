#!/usr/bin/env python3
"""DevTools Lab CLI.

Standalone, stdlib-only prototype for a future `devtools lab` command.

Purpose:
- create small Python/C++ probes,
- run/build/test them in isolation,
- generate VSCode launch/tasks entries,
- keep experimental work out of stable validate/tools flows.
"""

from __future__ import annotations

import argparse
import json
import os

try:
    import yaml
except ImportError:  # pragma: no cover
    yaml = None
import shutil
import subprocess
import sys
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Sequence, Tuple


DEFAULT_LAB_DIR = Path("dev_tools/lab")
DEFAULT_ARTIFACTS_DIR = Path(".DevJota/lab")


@dataclass
class CommandResult:
    name: str
    status: str
    message: str
    returncode: int = 0
    data: Optional[Dict[str, Any]] = None

    def to_dict(self) -> Dict[str, Any]:
        payload = asdict(self)
        if payload["data"] is None:
            payload.pop("data")
        return payload


def emit_result(result: CommandResult, *, json_mode: bool) -> int:
    if json_mode:
        print(json.dumps(result.to_dict(), indent=2, sort_keys=True))
    else:
        prefix = result.status.upper()
        print(f"[{prefix}] {result.name}: {result.message}")
        if result.data:
            for key, value in result.data.items():
                print(f"  {key}: {value}")
    return result.returncode


def emit_results(results: Sequence[CommandResult], *, json_mode: bool) -> int:
    fail = sum(1 for r in results if r.status.upper() == "FAIL")
    warn = sum(1 for r in results if r.status.upper() == "WARN")
    passed = sum(1 for r in results if r.status.upper() == "PASS")
    status = "FAIL" if fail else ("WARN" if warn else "PASS")
    rc = 1 if fail else 0
    if json_mode:
        print(json.dumps({
            "status": status,
            "summary": {"pass": passed, "warn": warn, "fail": fail, "total": len(results)},
            "results": [r.to_dict() for r in results],
        }, indent=2, sort_keys=True))
    else:
        for result in results:
            print(f"[{result.status.upper()}] {result.name}: {result.message}")
        print(f"Summary: PASS={passed} WARN={warn} FAIL={fail} TOTAL={len(results)}")
    return rc


def repo_root_from_args(args: argparse.Namespace) -> Path:
    return Path(args.root).resolve()


def lab_dir(root: Path, args: argparse.Namespace) -> Path:
    override = getattr(args, "lab_dir", None)
    return (root / override).resolve() if override else (root / DEFAULT_LAB_DIR).resolve()


def artifacts_dir(root: Path, args: argparse.Namespace, name: Optional[str] = None) -> Path:
    base = root / DEFAULT_ARTIFACTS_DIR
    return (base / name).resolve() if name else base.resolve()


def load_manifest(probe_dir: Path) -> Dict[str, Any]:
    manifest = probe_dir / "lab.json"
    if not manifest.exists():
        raise FileNotFoundError(f"missing manifest: {manifest}")
    with manifest.open("r", encoding="utf-8") as handle:
        return json.load(handle)


def save_manifest(probe_dir: Path, manifest: Dict[str, Any]) -> None:
    with (probe_dir / "lab.json").open("w", encoding="utf-8") as handle:
        json.dump(manifest, handle, indent=2, sort_keys=False)
        handle.write("\n")


def iter_probes(base: Path) -> Iterable[Tuple[str, Path, Dict[str, Any]]]:
    if not base.exists():
        return []
    items: List[Tuple[str, Path, Dict[str, Any]]] = []
    for child in sorted(base.iterdir()):
        if not child.is_dir() or child.name.startswith("_"):
            continue
        manifest = child / "lab.json"
        if not manifest.exists():
            continue
        try:
            data = load_manifest(child)
        except Exception as exc:  # pragma: no cover - defensive path
            data = {"id": child.name, "title": child.name, "status": "invalid", "error": str(exc)}
        items.append((child.name, child, data))
    return items


def safe_name(name: str) -> str:
    allowed = set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_")
    cleaned = "".join(ch if ch in allowed else "-" for ch in name.strip())
    cleaned = cleaned.strip("-_")
    if not cleaned:
        raise ValueError("empty probe name")
    if cleaned != name:
        raise ValueError(f"unsafe probe name {name!r}; suggested {cleaned!r}")
    return cleaned


def ensure_probe(root: Path, args: argparse.Namespace, name: str) -> Tuple[Path, Dict[str, Any]]:
    name = safe_name(name)
    path = lab_dir(root, args) / name
    manifest = load_manifest(path)
    return path, manifest


def write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def template_python(name: str) -> Dict[str, str]:
    module_name = name.replace("-", "_")
    return {
        "lab.json": json.dumps({
            "id": name,
            "title": f"{name} Python probe",
            "language": "python",
            "status": "experimental",
            "safety": "safe",
            "entrypoint": {"file": "main.py", "debug": "python"},
            "commands": {
                "run": {"argv": [sys.executable, "main.py"]},
                "test": {"argv": [sys.executable, "tests/test_main.py"]},
            },
            "debug": {
                "type": "python",
                "program": "main.py",
                "cwd": ".",
                "stopOnEntry": False,
            },
            "outputs": {"artifacts_dir": f".DevJota/lab/{name}"},
        }, indent=2) + "\n",
        "README.md": f"# {name}\n\nExperimental Python probe.\n\n## Commands\n\n```bash\npython3 dev_tools/lab_cli.py run {name}\npython3 dev_tools/lab_cli.py test {name}\npython3 dev_tools/lab_cli.py launch {name} --vscode --apply\n```\n",
        "main.py": f'''#!/usr/bin/env python3
"""Small Python probe generated by devtools lab."""

from __future__ import annotations


def compute(value: int) -> int:
    """Replace this tiny function with the piece you want to test."""
    return value * 2


def main() -> int:
    result = compute(21)
    print("{module_name}: result=", result)
    return 0 if result == 42 else 1


if __name__ == "__main__":
    raise SystemExit(main())
''',
        "tests/test_main.py": '''from pathlib import Path
import importlib.util


def load_main_module():
    module_path = Path(__file__).resolve().parents[1] / "main.py"
    spec = importlib.util.spec_from_file_location("probe_main", module_path)
    module = importlib.util.module_from_spec(spec)
    assert spec and spec.loader
    spec.loader.exec_module(module)
    return module


def test_compute_contract():
    module = load_main_module()
    assert module.compute(21) == 42


if __name__ == "__main__":
    test_compute_contract()
    print("test_compute_contract: OK")
''',
    }


def _cpp_lab_build_py(exe_name: str) -> str:
    template_path = Path(__file__).with_name("lab") / "_templates" / "cpp-cmake" / "lab_build.py"
    if template_path.exists():
        return template_path.read_text(encoding="utf-8").replace("{{exe_name}}", exe_name)
    raise FileNotFoundError(f"missing build template: {template_path}")


def template_cpp(name: str) -> Dict[str, str]:
    exe_name = name
    guard_name = name.replace("-", "_").upper()
    return {
        "lab.json": json.dumps({
            "id": name,
            "title": f"{name} C++ probe",
            "language": "cpp",
            "status": "experimental",
            "safety": "safe",
            "entrypoint": {"file": "main.cpp", "build": "cmake-or-g++", "debug": "gdb"},
            "commands": {
                "build": {"argv": ["python3", "lab_build.py", "build"]},
                "compile": {"argv": ["python3", "lab_build.py", "compile"]},
                "run": {"argv": [f".generated/build/{exe_name}"]},
                "test": {"argv": [f".generated/build/{exe_name}_tests"]},
            },
            "debug": {
                "type": "cppdbg",
                "program": f".generated/build/{exe_name}",
                "cwd": ".",
                "stopAtEntry": False,
                "MIMode": "gdb",
            },
            "outputs": {"artifacts_dir": f".DevJota/lab/{name}"},
        }, indent=2) + "\n",
        "README.md": f"# {name}\n\nExperimental C++ probe with CMake (g++ fallback).\n\n## Commands\n\n```bash\npython3 dev_tools/lab_cli.py build {name}\npython3 dev_tools/lab_cli.py test {name}\npython3 dev_tools/lab_cli.py run {name}\npython3 dev_tools/lab_cli.py launch {name} --vscode --apply\n```\n",
        "lab_build.py": _cpp_lab_build_py(exe_name),
        "CMakeLists.txt": f"""cmake_minimum_required(VERSION 3.16)
project({guard_name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable({exe_name} main.cpp)
add_executable({exe_name}_tests tests/test_main.cpp)

enable_testing()
add_test(NAME {exe_name}_tests COMMAND {exe_name}_tests)
""",
        "main.cpp": """#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int weight;
};

std::vector<Edge> sort_edges(std::vector<Edge> edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    return edges;
}

int main() {
    std::vector<Edge> edges = {{0, 1, 10}, {0, 2, 5}, {1, 2, 3}};
    auto sorted = sort_edges(edges);
    for (const auto& edge : sorted) {
        std::cout << edge.from << "-" << edge.to << " weight=" << edge.weight << std::endl;
    }
    return sorted.front().weight == 3 ? 0 : 1;
}
""",
        "tests/test_main.cpp": """#include <cassert>
#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int weight;
};

static std::vector<Edge> sort_edges(std::vector<Edge> edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    return edges;
}

int main() {
    std::vector<Edge> edges = {{0, 1, 10}, {0, 2, 5}, {1, 2, 3}};
    auto sorted = sort_edges(edges);
    assert(sorted.size() == 3);
    assert(sorted[0].weight == 3);
    assert(sorted[1].weight == 5);
    assert(sorted[2].weight == 10);
    return 0;
}
""",
    }


def command_from_manifest(manifest: Dict[str, Any], command_name: str) -> List[str]:
    commands = manifest.get("commands", {})
    if command_name not in commands:
        raise KeyError(f"probe {manifest.get('id')} has no command {command_name!r}")
    argv = commands[command_name].get("argv")
    if not isinstance(argv, list) or not all(isinstance(x, str) for x in argv):
        raise ValueError(f"invalid argv for command {command_name!r}")
    return argv


def run_subprocess(argv: List[str], cwd: Path) -> int:
    print("$", " ".join(argv))
    proc = subprocess.run(argv, cwd=str(cwd), text=True)
    return int(proc.returncode)


def cmd_list(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    base = lab_dir(root, args)
    probes = []
    for name, path, manifest in iter_probes(base):
        probes.append({
            "id": manifest.get("id", name),
            "title": manifest.get("title", name),
            "language": manifest.get("language", "unknown"),
            "status": manifest.get("status", "unknown"),
            "safety": manifest.get("safety", "unknown"),
            "path": str(path.relative_to(root)) if path.is_relative_to(root) else str(path),
        })
    result = CommandResult(
        name="lab list",
        status="PASS",
        message=f"{len(probes)} probe(s) found",
        data={"probes": probes, "lab_dir": str(base)},
    )
    return emit_result(result, json_mode=args.json)


def cmd_new(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    name = safe_name(args.name)
    base = lab_dir(root, args)
    target = base / name
    if target.exists() and not args.force:
        return emit_result(CommandResult("lab new", "FAIL", f"probe already exists: {target}", 1), json_mode=args.json)
    if args.language == "python":
        files = template_python(name)
    elif args.language == "cpp":
        files = template_cpp(name)
    else:  # pragma: no cover - argparse prevents this
        return emit_result(CommandResult("lab new", "FAIL", f"unsupported language: {args.language}", 1), json_mode=args.json)
    target.mkdir(parents=True, exist_ok=True)
    for rel, text in files.items():
        write_text(target / rel, text)
    out = artifacts_dir(root, args, name)
    out.mkdir(parents=True, exist_ok=True)
    return emit_result(CommandResult(
        "lab new",
        "PASS",
        f"created {args.language} probe {name}",
        data={"path": str(target), "artifacts_dir": str(out)},
    ), json_mode=args.json)


def cmd_show(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    try:
        path, manifest = ensure_probe(root, args, args.name)
    except Exception as exc:
        return emit_result(CommandResult("lab show", "FAIL", str(exc), 1), json_mode=args.json)
    data = dict(manifest)
    data["path"] = str(path)
    return emit_result(CommandResult("lab show", "PASS", f"loaded {args.name}", data=data), json_mode=args.json)


def run_manifest_command(args: argparse.Namespace, command_name: str) -> int:
    root = repo_root_from_args(args)
    try:
        path, manifest = ensure_probe(root, args, args.name)
        argv = command_from_manifest(manifest, command_name)
    except Exception as exc:
        return emit_result(CommandResult(f"lab {command_name}", "FAIL", str(exc), 1), json_mode=args.json)
    if args.dry_run:
        return emit_result(CommandResult(f"lab {command_name}", "PASS", "dry-run", data={"cwd": str(path), "argv": argv}), json_mode=args.json)
    if command_name == "build" and shutil.which(argv[0]) is None:
        return emit_result(CommandResult("lab build", "WARN", f"missing executable: {argv[0]}", 0, {"argv": argv}), json_mode=args.json)
    rc = run_subprocess(argv, cwd=path)
    status = "PASS" if rc == 0 else "FAIL"
    return emit_result(CommandResult(f"lab {command_name}", status, f"returncode={rc}", rc, {"cwd": str(path), "argv": argv}), json_mode=args.json)


def cmd_build(args: argparse.Namespace) -> int:
    # CMake has configure and compile phases in this template.
    root = repo_root_from_args(args)
    try:
        path, manifest = ensure_probe(root, args, args.name)
        build_argv = command_from_manifest(manifest, "build")
        compile_argv = command_from_manifest(manifest, "compile") if "compile" in manifest.get("commands", {}) else []
    except Exception as exc:
        return emit_result(CommandResult("lab build", "FAIL", str(exc), 1), json_mode=args.json)
    if args.dry_run:
        return emit_result(CommandResult("lab build", "PASS", "dry-run", data={"cwd": str(path), "steps": [build_argv, compile_argv]}), json_mode=args.json)
    results: List[CommandResult] = []
    if shutil.which(build_argv[0]) is None:
        results.append(CommandResult("lab build configure", "WARN", f"missing executable: {build_argv[0]}", 0, {"argv": build_argv}))
        return emit_results(results, json_mode=args.json)
    rc1 = run_subprocess(build_argv, cwd=path)
    results.append(CommandResult("lab build configure", "PASS" if rc1 == 0 else "FAIL", f"returncode={rc1}", rc1, {"argv": build_argv}))
    if rc1 == 0 and compile_argv:
        rc2 = run_subprocess(compile_argv, cwd=path)
        results.append(CommandResult("lab build compile", "PASS" if rc2 == 0 else "FAIL", f"returncode={rc2}", rc2, {"argv": compile_argv}))
    return emit_results(results, json_mode=args.json)


def cmd_run(args: argparse.Namespace) -> int:
    return run_manifest_command(args, "run")


def cmd_test(args: argparse.Namespace) -> int:
    return run_manifest_command(args, "test")


def cmd_subtest(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    try:
        path, manifest = ensure_probe(root, args, args.name)
    except Exception as exc:
        return emit_result(CommandResult("lab subtest", "FAIL", str(exc), 1), json_mode=args.json)

    subtests = manifest.get("subtests", {})
    probe_id = manifest.get("id", args.name)
    probe_title = manifest.get("title", args.name)

    if args.subcommand == "info":
        data = {
            "id": probe_id,
            "title": probe_title,
            "subtests": {name: {"argv": spec.get("argv", [])} for name, spec in subtests.items()},
        }
        return emit_result(
            CommandResult("lab subtest info", "PASS", f"{len(subtests)} subtest(s)", data=data),
            json_mode=args.json,
        )

    if args.subcommand == "status":
        results: List[CommandResult] = []
        for name, spec in subtests.items():
            argv = spec.get("argv", [])
            exe_path = path / argv[0] if argv else path / "."
            exists = exe_path.exists() and exe_path.is_file()
            status = "PASS" if exists else "FAIL"
            message = "executable exists" if exists else "executable missing"
            results.append(
                CommandResult(
                    f"subtest {name}",
                    status,
                    message,
                    0 if exists else 1,
                    {"argv": argv, "path": str(exe_path)},
                )
            )
        return emit_results(results, json_mode=args.json)

    if args.subcommand == "exec":
        if args.subtest_name:
            if args.subtest_name not in subtests:
                return emit_result(
                    CommandResult("lab subtest exec", "FAIL", f"unknown subtest: {args.subtest_name}", 1),
                    json_mode=args.json,
                )
            items = [(args.subtest_name, subtests[args.subtest_name])]
        else:
            items = list(subtests.items())

        results: List[CommandResult] = []
        for name, spec in items:
            argv = spec.get("argv", [])
            if not argv:
                results.append(CommandResult(f"subtest {name}", "FAIL", "empty argv", 1, {"argv": argv}))
                continue
            exe_path = path / argv[0]
            if not exe_path.exists():
                results.append(
                    CommandResult(
                        f"subtest {name}",
                        "FAIL",
                        f"executable missing: {exe_path}",
                        1,
                        {"argv": argv},
                    )
                )
                continue
            rc = run_subprocess(argv, cwd=path)
            status = "PASS" if rc == 0 else "FAIL"
            results.append(
                CommandResult(
                    f"subtest {name}",
                    status,
                    f"returncode={rc}",
                    rc,
                    {"argv": argv},
                )
            )
        return emit_results(results, json_mode=args.json)

    return emit_result(
        CommandResult("lab subtest", "FAIL", f"unknown subcommand: {args.subcommand}", 1),
        json_mode=args.json,
    )


def vscode_launch_entry(name: str, manifest: Dict[str, Any]) -> Dict[str, Any]:
    debug = manifest.get("debug", {})
    language = manifest.get("language")
    if language == "python":
        return {
            "name": f"Lab: {name}",
            "type": "python",
            "request": "launch",
            "program": f"${{workspaceFolder}}/dev_tools/lab/{name}/{debug.get('program', 'main.py')}",
            "cwd": f"${{workspaceFolder}}/dev_tools/lab/{name}",
            "console": "integratedTerminal",
            "justMyCode": True,
        }
    if language == "cpp":
        return {
            "name": f"Lab: {name}",
            "type": "cppdbg",
            "request": "launch",
            "program": f"${{workspaceFolder}}/dev_tools/lab/{name}/{debug.get('program', '.generated/build/' + name)}",
            "cwd": f"${{workspaceFolder}}/dev_tools/lab/{name}",
            "MIMode": debug.get("MIMode", "gdb"),
            "stopAtEntry": bool(debug.get("stopAtEntry", False)),
            "preLaunchTask": f"Lab Build: {name}",
        }
    return {
        "name": f"Lab: {name}",
        "type": "node",
        "request": "launch",
        "program": f"${{workspaceFolder}}/dev_tools/lab/{name}",
    }


def vscode_task_entry(name: str, manifest: Dict[str, Any]) -> Dict[str, Any]:
    commands = manifest.get("commands", {})
    if "build" in commands:
        cmd = ["python3", "dev_tools/lab_cli.py", "build", name]
    else:
        cmd = ["python3", "dev_tools/lab_cli.py", "run", name]
    return {
        "label": f"Lab Build: {name}",
        "type": "shell",
        "command": " ".join(cmd),
        "group": "build",
        "problemMatcher": [],
    }


def merge_vscode_json(path: Path, key: str, entry: Dict[str, Any], *, apply: bool) -> Tuple[str, Dict[str, Any]]:
    if path.exists():
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except json.JSONDecodeError:
            raise ValueError(f"invalid JSON: {path}")
    else:
        if key == "configurations":
            data = {"version": "0.2.0", key: []}
        else:
            data = {"version": "2.0.0", key: []}
    items = data.setdefault(key, [])
    if not isinstance(items, list):
        raise ValueError(f"{path}: {key} is not a list")
    name_key = "name" if key == "configurations" else "label"
    wanted = entry[name_key]
    replaced = False
    for idx, item in enumerate(items):
        if isinstance(item, dict) and item.get(name_key) == wanted:
            items[idx] = entry
            replaced = True
            break
    if not replaced:
        items.append(entry)
    if apply:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")
    action = "updated" if replaced else "added"
    return action, data


def cmd_launch(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    try:
        path, manifest = ensure_probe(root, args, args.name)
    except Exception as exc:
        return emit_result(CommandResult("lab launch", "FAIL", str(exc), 1), json_mode=args.json)
    if not args.vscode:
        return emit_result(CommandResult("lab launch", "FAIL", "only --vscode is supported in this pack", 1), json_mode=args.json)
    launch_entry = vscode_launch_entry(args.name, manifest)
    task_entry = vscode_task_entry(args.name, manifest)
    if args.dry_run:
        return emit_result(CommandResult("lab launch", "PASS", "dry-run", data={"launch": launch_entry, "task": task_entry}), json_mode=args.json)
    if not args.apply:
        return emit_result(CommandResult("lab launch", "WARN", "no files written; pass --apply to update .vscode", 0, {"launch": launch_entry, "task": task_entry}), json_mode=args.json)
    launch_path = root / ".vscode" / "launch.json"
    task_path = root / ".vscode" / "tasks.json"
    try:
        launch_action, _ = merge_vscode_json(launch_path, "configurations", launch_entry, apply=True)
        task_action, _ = merge_vscode_json(task_path, "tasks", task_entry, apply=True)
    except Exception as exc:
        return emit_result(CommandResult("lab launch", "FAIL", str(exc), 1), json_mode=args.json)
    return emit_result(CommandResult("lab launch", "PASS", "VSCode launcher generated", data={
        "launch_json": str(launch_path),
        "tasks_json": str(task_path),
        "launch_action": launch_action,
        "task_action": task_action,
    }), json_mode=args.json)


def cmd_promote(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    try:
        path, manifest = ensure_probe(root, args, args.name)
    except Exception as exc:
        return emit_result(CommandResult("lab promote", "FAIL", str(exc), 1), json_mode=args.json)
    tool_id = manifest.get("id", args.name).replace("-", ".")
    tool_spec = {
        "id": tool_id,
        "title": manifest.get("title", args.name),
        "source_probe": str(path.relative_to(root)) if path.is_relative_to(root) else str(path),
        "kind": "lab-promoted-tool-candidate",
        "safety": manifest.get("safety", "safe"),
        "status": "candidate",
        "command": manifest.get("commands", {}).get("run", {}),
        "outputs": manifest.get("outputs", {}),
    }
    target = root / "dev_tools" / "tools" / f"{tool_id}.tool.yml"
    if args.dry_run:
        return emit_result(CommandResult("lab promote", "PASS", "dry-run", data={"target": str(target), "tool_spec": tool_spec}), json_mode=args.json)
    target.parent.mkdir(parents=True, exist_ok=True)
    if yaml is None:
        target_json = target.with_suffix(".json")
        target_json.write_text(json.dumps(tool_spec, indent=2) + "\n", encoding="utf-8")
    else:
        target.write_text(yaml.dump(tool_spec, sort_keys=False, allow_unicode=True), encoding="utf-8")
    manifest["status"] = "candidate"
    save_manifest(path, manifest)
    return emit_result(CommandResult("lab promote", "PASS", "tool candidate written", data={"target": str(target)}), json_mode=args.json)




def _load_tool_spec(path: Path) -> Dict[str, Any]:
    raw = path.read_text(encoding="utf-8")
    if path.suffix in (".yaml", ".yml"):
        if yaml is None:
            raise RuntimeError(f"PyYAML required to read {path}")
        return yaml.safe_load(raw)
    return json.loads(raw)


def _iter_tools(root: Path) -> Iterable[Tuple[str, Path, Dict[str, Any]]]:
    tools_dir = root / "dev_tools" / "tools"
    if not tools_dir.exists():
        return []
    items: List[Tuple[str, Path, Dict[str, Any]]] = []
    for path in sorted(tools_dir.rglob("*")):
        if not path.is_file() or path.suffix not in (".json", ".yml", ".yaml"):
            continue
        try:
            data = _load_tool_spec(path)
        except Exception as exc:  # pragma: no cover - defensive path
            data = {"id": path.stem, "title": path.stem, "status": "invalid", "error": str(exc)}
        tool_id = data.get("id") if isinstance(data, dict) else path.stem
        items.append((tool_id or path.stem, path, data))
    return items


def cmd_tools_list(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    tools = []
    for tool_id, path, spec in _iter_tools(root):
        tools.append({
            "id": tool_id,
            "title": spec.get("title", tool_id) if isinstance(spec, dict) else tool_id,
            "status": spec.get("status", "unknown") if isinstance(spec, dict) else "unknown",
            "safety": spec.get("safety", "unknown") if isinstance(spec, dict) else "unknown",
            "path": str(path.relative_to(root)) if path.is_relative_to(root) else str(path),
        })
    result = CommandResult(
        name="tools list",
        status="PASS",
        message=f"{len(tools)} tool(s) found",
        data={"tools": tools, "tools_dir": str(root / "dev_tools" / "tools")},
    )
    return emit_result(result, json_mode=args.json)


def cmd_tool_show(args: argparse.Namespace) -> int:
    root = repo_root_from_args(args)
    wanted = args.tool_id
    matches = []
    for tool_id, path, spec in _iter_tools(root):
        if tool_id == wanted or path.stem == wanted:
            matches.append((tool_id, path, spec))
    if not matches:
        return emit_result(CommandResult("tool show", "FAIL", f"tool not found: {wanted}", 1), json_mode=args.json)
    if len(matches) > 1:
        paths = [str(p) for _, p, _ in matches]
        return emit_result(CommandResult("tool show", "FAIL", f"ambiguous tool id: {wanted}", 1, {"matches": paths}), json_mode=args.json)
    tool_id, path, spec = matches[0]
    data = dict(spec) if isinstance(spec, dict) else {"spec": spec}
    data["path"] = str(path)
    return emit_result(CommandResult("tool show", "PASS", f"loaded {tool_id}", data=data), json_mode=args.json)


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="DevTools Lab CLI - standalone prototype")
    parser.add_argument("--root", default=".", help="repository root, defaults to current directory")
    parser.add_argument("--lab-dir", default=str(DEFAULT_LAB_DIR), help="lab directory relative to root")
    sub = parser.add_subparsers(dest="command", required=True)

    def add_json(p: argparse.ArgumentParser) -> None:
        p.add_argument("--json", action="store_true", help="emit machine-readable JSON")

    p = sub.add_parser("list", help="list lab probes")
    add_json(p)
    p.set_defaults(func=cmd_list)

    p = sub.add_parser("new", help="create a new lab probe")
    p.add_argument("language", choices=["python", "cpp"])
    p.add_argument("name")
    p.add_argument("--force", action="store_true")
    add_json(p)
    p.set_defaults(func=cmd_new)

    p = sub.add_parser("show", help="show a lab probe manifest")
    p.add_argument("name")
    add_json(p)
    p.set_defaults(func=cmd_show)

    for command_name, func in [("run", cmd_run), ("test", cmd_test), ("build", cmd_build)]:
        p = sub.add_parser(command_name, help=f"{command_name} a lab probe")
        p.add_argument("name")
        p.add_argument("--dry-run", action="store_true")
        add_json(p)
        p.set_defaults(func=func)

    p = sub.add_parser("subtest", help="manage probe subtests")
    p.add_argument("name", help="probe id")
    p.add_argument("subcommand", choices=["info", "status", "exec"], help="subtest action")
    p.add_argument("subtest_name", nargs="?", help="specific subtest to execute (exec only)")
    add_json(p)
    p.set_defaults(func=cmd_subtest)

    p = sub.add_parser("launch", help="generate launcher entries")
    p.add_argument("name")
    p.add_argument("--vscode", action="store_true", help="generate VSCode launch/task entries")
    p.add_argument("--apply", action="store_true", help="write .vscode files")
    p.add_argument("--dry-run", action="store_true")
    add_json(p)
    p.set_defaults(func=cmd_launch)

    p = sub.add_parser("promote", help="promote a probe to a tool candidate")
    p.add_argument("name")
    p.add_argument("--to", choices=["tools"], default="tools")
    p.add_argument("--dry-run", action="store_true")
    add_json(p)
    p.set_defaults(func=cmd_promote)

    p = sub.add_parser("tools", help="list promoted tool candidates")
    add_json(p)
    p.set_defaults(func=cmd_tools_list)

    p = sub.add_parser("tool", help="show a tool candidate spec")
    p.add_argument("tool_id")
    add_json(p)
    p.set_defaults(func=cmd_tool_show)

    return parser


def main(argv: Optional[Sequence[str]] = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        return int(args.func(args))
    except KeyboardInterrupt:
        print("Interrupted", file=sys.stderr)
        return 130


if __name__ == "__main__":
    raise SystemExit(main())
