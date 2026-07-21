# Repository Guidelines

## Project Structure & Module Organization
This repository combines Hall C NPS Geant4 simulation code with ROOT-based reconstruction utilities.

- `README.md` documents the main SIMC-to-Geant4 workflow and expected JLab/ifarm environment.
- `HallC_NPS/DVCS_evt_gen/DVCS/` is the primary DVCS Geant4 application. C++ sources are in `src/`, headers in `include/`, runtime macros in `macros/`, and local builds normally go in `build/`.
- `HallC_NPS/glass_prototype/`, `jlab_HallC_NPS_PbWO4/`, and `jlab_HallC_NPS_Energy_Resolution_Simulation/` are maintained Geant4 variants with similar `source/src`, `source/include`, and `macros` layouts.
- `NPS_SOFT/` contains ROOT/C++ clustering, trigger, decoder, and calibration code used by the simulation.
- `KinC_list.txt` provides run-dependent kinematic configuration.

## Build, Test, and Development Commands
Load the expected JLab modules before building:

```bash
module purge
module use /group/halla/modulefiles
module load geant4/11.2.1
module load root/6.30.04
```

Build the reconstruction libraries:

```bash
make -C NPS_SOFT biglib
```

Configure and build the DVCS Geant4 executable:

```bash
cmake -S HallC_NPS/DVCS_evt_gen/DVCS -B HallC_NPS/DVCS_evt_gen/DVCS/build -DNPS_SOFT_ROOT="$PWD/NPS_SOFT"
cmake --build HallC_NPS/DVCS_evt_gen/DVCS/build
```

Run a batch smoke test with a SIMC ROOT file:

```bash
HallC_NPS/DVCS_evt_gen/DVCS/build/DVCS input.root h10 10 test.root --batch
```

## Coding Style & Naming Conventions
Use C++17 for CMake-managed Geant4 code. Follow the existing Geant4 style: class names in `UpperCamelCase`, methods in `lowerCamelCase` or established Geant4 names, headers as `.hh`, and implementations as `.cc`. Keep ROOT/NPS_SOFT additions consistent with nearby `.cxx`/`.h` files. Preserve existing indentation and avoid broad reformatting.

## Testing Guidelines
There is no formal automated test suite in this repository. Validate changes with a minimal build and a short batch run using representative SIMC input. For visualization changes, check `--vis`, `--vis-single`, and `--vis-seq` when an interactive Geant4 UI is available. Do not commit generated `.root`, `.log`, `.o`, `.so`, `.a`, or build-directory outputs.

## Commit & Pull Request Guidelines
Recent commits use short, direct summaries such as `updated readme` and `fixed the phot... branches`. Keep commit messages concise and behavior-focused. Pull requests should describe the physics or reconstruction impact, list build/test commands run, identify required external inputs such as SIMC files or kinematic settings, and mention any changes to output ROOT branches or macro behavior.

## Configuration Notes
Prefer passing `-DNPS_SOFT_ROOT=/path/to/NPS_SOFT` instead of relying on implicit library discovery. Keep site-specific paths and large generated data out of tracked files; document reproducible environment assumptions in `README.md` or the relevant subdirectory README.
