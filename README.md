# Simple Virtual Machine

Small educational virtual machine implemented in C with a small instruction set.

## Build

### Make

```bash
make all
```

### Nix

If you use Nix:

```bash
nix-build
```

### Manual

```bash
gcc -Wall src/zvm.c src/zvm_instruction.c src/zvm_exception.c src/zvm_io.c -o zvm
```

## Run

```bash
./zvm
```
