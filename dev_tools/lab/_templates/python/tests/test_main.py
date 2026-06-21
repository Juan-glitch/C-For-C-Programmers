from pathlib import Path
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
