# DVCS Geant4 + SIMC Reconstruction Project

This repository contains a Geant4-based simulation and reconstruction pipeline that reads SIMC output (ROOT) and runs a calorimeter + detector simulation, including clustering and ntuple production.

This README explains how to build, how to run, and how to use the new KinC list printing / run-selection feature.

---

## Requirements

- C++ compiler with C++11 (or newer) support (g++ / clang++)
- CMake (>= 3.10 recommended)
- Geant4 (compiled with the same compiler; environment variables sourced)
- ROOT (for reading SIMC files and writing ntuples)
- CLHEP (usually included with Geant4)
- `make` or `ninja` (or use `cmake --build`)

Make sure your environment is configured for Geant4 and ROOT. Example (bash):

```bash
module purge
module use /group/halla/modulefiles
module load geant4/11.2.1
module load root/6.30.04
````

---

## Build

From the project root:

```bash
mkdir -p build
cd build
cmake ..                 # add -DGeant4_DIR=/path/to/geant4/cmake if necessary
make -j4                 # or: cmake --build . -- -j4
```

If `HistoManager.cc` or other new sources were added, ensure they are included in `CMakeLists.txt` so they compile and link into the `DVCS` executable.

---

## Run

Run the built executable (from the `build` directory or with full path):

```
./DVCS <simc.root> [tree] [nEvents] [out.root] [--batch] [--vis]
```

Examples:

* Interactive run (prompts for SIMC file and prints kinclist):

  ```bash
  ./DVCS
  ```

  The program will print a concise KinC list (run number + kinematic text) using the KinC file path `../../../../KinC_list.txt` (relative to where the program runs). You can pick a run number and the program will automatically apply that run's configuration.

* Provide SIMC file and options on the command line:

  ```bash
  ./DVCS /path/to/simc.root h10 1000 my_output.root --batch
  ```

* Visual mode (requires X and Geant4 visualization support):

  ```bash
  ./DVCS /path/to/simc.root h10 100 --vis
  ```

---

## New feature: KinC list printing & run selection

At startup the program prints a compact view of `KinC_list.txt` (`../../../../KinC_list.txt` by default). Each printed line shows:

```
RunNumber   <rest of line (kinematic description)>
```

This makes it easier to choose which run to simulate. Enter the chosen `runNumber` at the prompt.

If your KinC list has a different structure, or you want to provide a custom path, you can edit `main.cc` (the `kinclist_path` constant) or pass environment variables / add a CLI option — I can help add that.

---

## Output

* The program produces a ROOT output file (default `geant_output.root`) containing:

  * per-crystal energy deposition (`edep[...]`)
  * photon & cluster information
  * the new vector branches for clusters: `nClusters`, `clust_E`, `clust_X`, `clust_Y`, `clust_Size`
  * mirrored SIMC branches if a SIMC ROOT path and tree are supplied
---

## Contact / Next steps
Avnish Singh; singhav@cua.edu, singhav@jlab.org
```
