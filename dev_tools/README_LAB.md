# DevTools Lab

`lab` is the staging area for small Python/C++ probes before they become official tools or validations.

## Commands

```bash
python3 dev_tools/lab_cli.py list
python3 dev_tools/lab_cli.py new python <name>
python3 dev_tools/lab_cli.py new cpp <name>
python3 dev_tools/lab_cli.py show <name>
python3 dev_tools/lab_cli.py run <name>
python3 dev_tools/lab_cli.py test <name>
python3 dev_tools/lab_cli.py build <name>
python3 dev_tools/lab_cli.py launch <name> --vscode --dry-run
python3 dev_tools/lab_cli.py promote <name> --dry-run
```

## Lifecycle

```text
experimental -> candidate -> promoted -> deprecated
```

## Directory policy

```text
dev_tools/lab        versionable probes
dev_tools/tools      official/promoted tools
.DevJota/lab         outputs, logs, reports, local artifacts
```

## C++ debugging

Generated C++ probes use CMake Debug builds and can be launched from VSCode using `cppdbg`/`gdb`.

## Python debugging

Generated Python probes can be launched directly with VSCode Python debugger.
