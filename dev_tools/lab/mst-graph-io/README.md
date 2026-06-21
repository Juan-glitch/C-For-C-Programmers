# MST Graph I/O probe

Lab probe: `mst-graph-io`.

Builds with CMake (preferred) or direct `g++` fallback. The source files from
`src/Module 4/Assignment4_MST` are referenced via relative paths, so the probe
always uses the current assignment implementation.

## Commands

```bash
python3 dev_tools/lab_cli.py build mst-graph-io
python3 dev_tools/lab_cli.py test mst-graph-io
python3 dev_tools/lab_cli.py run mst-graph-io
python3 dev_tools/lab_cli.py launch mst-graph-io --vscode --apply
```
