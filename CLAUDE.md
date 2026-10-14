# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

C++20 solutions to Project Euler problems. Identifiers, comments and output are in French (`nombre`, `premiers`, `crible`, `chiffres`, `solution`, …); keep new code in the same style.

## Build

Dependencies: clang/clang++ (hard-coded in `CMakeLists.txt`), Boost ≥ 1.80 (`unit_test_framework`, `date_time`), GMP, MPFR. The custom find modules are in `install/`.

```sh
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release -j
```

Warnings are strict: `-Werror -Weverything`, with only a few exclusions. Any new warning breaks the build. Silence it locally with `#pragma clang diagnostic push/ignored/pop`, the way the existing code does.

## Running problems

`ProjectEuler` must be run from the build directory. It opens `data/...` with relative paths, and CMake copies `data/` into the build tree at configure time.

```sh
cd cmake-build-release
./ProjectEuler 918          # single problem
./ProjectEuler 1-50 99,100  # ranges (a-b or a:b) and comma lists
./ProjectEuler              # prompts on stdin; "all" runs every problem
```

Each result is compared with `data/solutions.txt` (lines of `<numero> <solution>`). A match prints in green, a mismatch prints `ERREUR !` in red, and a run longer than 60 s prints a warning.

## Tests

The Boost.Test suites in `tests/` cover the `maths/` and `utils/` libraries, not the problems.

```sh
./ProjectEulerTest                           # all suites
./ProjectEulerTest --run_test=test_fibonacci # one suite
./ProjectEulerTest --run_test=test_fibonacci/nombres_fibonacci
```

New test files must be added to the explicit list in `tests/CMakeLists.txt`.

## Architecture

- `utils/` is a shared library. It holds GMP/MPFR wrappers (`mpz_nombre`, `mpq_fraction`, `mpf_nombre`), `multidimension.h` (nested vectors), `Timer`, iterator helpers, and stream `operator<<` for containers (`format.h`, `format/*.h`).
- `maths/` is a shared library built on `utils`. It holds number-theory and combinatorics tools: `premiers` (prime sieves such as `premiers::crible2`), `arithmetique` (gcd, divisors, φ, …), modular arithmetic, `matrice`, `polynome`, `fibonacci`, `fenwick`, `graphe`, `diophantienne`, `pythagoricien`, and others.
- `problemes/` is a shared library containing one `.cpp` per problem. Problems register themselves through a static-initialisation registry (`problemes.h`):

  ```cpp
  #include "problemes.h"
  ENREGISTRER_PROBLEME(918, "Recursive Sequence Summation") {
      // problem statement as a comment
      return std::to_string(result);   // answer as a string
  }
  ```

  `ENREGISTRER_PROBLEME` defines `probleme<N>()` and a static `Probleme` object that adds it to `RegistreProbleme`. Problems 1–399 live in `probleme0xx/` … `probleme3xx/`. Problems ≥ 400 sit flat in `problemes/` as `probleme<N>.cpp`. Both locations are picked up by glob/`aux_source_directory`, so **re-run CMake after adding a problem file**. File-local helpers go in an anonymous namespace.
- `euler.cpp` / `test.cpp` are the two executables' entry points.

## Adding a solved problem

A typical commit (for example "Problème 918 …") adds `problemes/probleme<N>.cpp` and appends `<N> <answer>` to `data/solutions.txt`. Input files from Project Euler go in `data/` (for example `data/p107_network.txt`).
