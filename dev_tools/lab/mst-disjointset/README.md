# MST DisjointSet probe

Lab probe: `mst-disjointset`.

Builds with CMake (preferred) or direct `g++` fallback. The source files from
`src/Module 4/Assignment4_MST` are referenced via relative paths, so the probe
always uses the current assignment implementation.

## Commands

```bash
python3 dev_tools/lab_cli.py build mst-disjointset
python3 dev_tools/lab_cli.py test mst-disjointset
python3 dev_tools/lab_cli.py run mst-disjointset
python3 dev_tools/lab_cli.py launch mst-disjointset --vscode --apply
```
