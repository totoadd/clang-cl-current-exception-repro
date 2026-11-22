# clang-cl noexcept Reproducer

Minimal reproducer for an issue where `std::current_exception()` returns `nullptr` in a `std::terminate` handler when a `noexcept` function is called through a potentially-throwing function pointer inside a matching `try`/`catch`.

The issue reproduces with clang-cl 22.1.3 and 23.1.6, but not with MSVC.

## Reproducers

- `test.cpp`: Uses `void (*)()`, reproducing the issue with clang-cl.
- `test_noexcept.cpp`: Uses `void (*)() noexcept`, which works correctly with both compilers.

## Results

| Compiler | `test.cpp` | `test_noexcept.cpp` |
|---|---|---|
| clang-cl | `nullptr` (exit code 1) | Valid exception (exit code 42) |
| MSVC | Valid exception (exit code 42) | Valid exception (exit code 42) |

The GitHub Actions workflow compiles and runs both reproducers on Windows, checking that the results match the table above.

## AI Assistance

OpenAI GPT-6 was used in Codex to help investigate the issue and generate the initial reproducer, which was then manually edited and tested.

ChatGPT was used to review the bug report and generate the GitHub Actions workflow and this README.
