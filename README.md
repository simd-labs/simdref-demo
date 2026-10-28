# simdref demo

A small x86-64 program to open in an editor with a simdref plugin. Each file shows one feature of `simdref-lsp`.

| File | What the editor shows |
|---|---|
| `intrinsics.c` | Hover on an intrinsic, for example `_mm256_fmadd_ps`, to show its simdref page. |
| `inline_asm.c` | Each instruction in an `asm(...)` string gets a one-line summary at the end of its line. Hover shows the full page. |
| `sum.s` | Each instruction line gets a one-line summary. Hover shows the full page. |

Editor plugins:

- Zed: [zed-asm-intrinsics](https://github.com/simd-labs/zed-asm-intrinsics). For hints in `sum.s`, also install the Zed `assembly` extension.
- VS Code: [vscode-simdref](https://github.com/simd-labs/vscode-simdref)
- Neovim: [nvim-simdref](https://github.com/simd-labs/nvim-simdref)
- JetBrains: [jetbrains-simdref](https://github.com/simd-labs/jetbrains-simdref)

The `.clangd` file adds `-mavx2 -mfma -mpopcnt`, so clangd does not mark the intrinsics as errors.

## Build and check

The program needs an x86-64 CPU with AVX2, FMA and POPCNT.

```sh
make check
```

`main.c` compares each kernel with a scalar loop and prints one `ok` or `FAIL` line per check. The exit status is 1 if a check fails.
