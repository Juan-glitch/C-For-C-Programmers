from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
CLI = ROOT / "dev_tools" / "lab_cli.py"


def run_cli(tmp_path: Path, *args: str):
    repo = tmp_path / "repo"
    repo.mkdir(exist_ok=True)
    dev_tools = repo / "dev_tools"
    dev_tools.mkdir(exist_ok=True)
    target_cli = dev_tools / "lab_cli.py"
    target_cli.write_text(CLI.read_text(encoding="utf-8"), encoding="utf-8")
    return subprocess.run(
        [sys.executable, str(target_cli), "--root", str(repo), *args],
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )


def test_help_smoke(tmp_path: Path):
    result = run_cli(tmp_path, "--help")
    assert result.returncode == 0
    assert "DevTools Lab CLI" in result.stdout


def test_new_python_and_list_json(tmp_path: Path):
    created = run_cli(tmp_path, "new", "python", "hello-python", "--json")
    assert created.returncode == 0, created.stderr
    payload = json.loads(created.stdout)
    assert payload["status"] == "PASS"

    listed = run_cli(tmp_path, "list", "--json")
    assert listed.returncode == 0
    payload = json.loads(listed.stdout)
    assert payload["data"]["probes"][0]["id"] == "hello-python"


def test_run_dry_run_is_json(tmp_path: Path):
    assert run_cli(tmp_path, "new", "python", "hello-python").returncode == 0
    result = run_cli(tmp_path, "run", "hello-python", "--dry-run", "--json")
    assert result.returncode == 0
    payload = json.loads(result.stdout)
    assert payload["status"] == "PASS"
    assert payload["data"]["argv"]


def test_cpp_probe_generates_cmake_files(tmp_path: Path):
    result = run_cli(tmp_path, "new", "cpp", "hello-cpp", "--json")
    assert result.returncode == 0
    payload = json.loads(result.stdout)
    probe = Path(payload["data"]["path"])
    assert (probe / "CMakeLists.txt").exists()
    assert (probe / "main.cpp").exists()
    assert (probe / "tests" / "test_main.cpp").exists()


def test_vscode_launch_dry_run(tmp_path: Path):
    assert run_cli(tmp_path, "new", "python", "hello-python").returncode == 0
    result = run_cli(tmp_path, "launch", "hello-python", "--vscode", "--dry-run", "--json")
    assert result.returncode == 0
    payload = json.loads(result.stdout)
    assert payload["status"] == "PASS"
    assert payload["data"]["launch"]["name"] == "Lab: hello-python"


def test_promote_dry_run_creates_tool_candidate_payload(tmp_path: Path):
    assert run_cli(tmp_path, "new", "python", "hello-python").returncode == 0
    result = run_cli(tmp_path, "promote", "hello-python", "--dry-run", "--json")
    assert result.returncode == 0
    payload = json.loads(result.stdout)
    assert payload["data"]["tool_spec"]["status"] == "candidate"
