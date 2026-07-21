# Exclusive / SIDIS π⁰ Geant4 + SIMC Reconstruction Framework

This repository contains a Geant4-based detector simulation and reconstruction framework for exclusive and SIDIS π⁰ reactions in Hall C. It interfaces directly with SIMC ROOT output, propagates generated particles through a realistic NPS calorimeter and spectrometer geometry, performs clustering and trigger emulation, and writes analysis-ready ROOT ntuples.

The framework provides:

* SIMC → Geant4 event transport
* Full electromagnetic shower simulation in the NPS calorimeter
* Cluster reconstruction and trigger response using NPS_SOFT
* Event-by-event truth association of primary photons with deposited energy
* Automatic kinematic configuration via the Hall C KinC list

This work builds upon the earlier simulation framework by Hao Huang:
[https://github.com/hhuang-hep/NPS2023_Simulation](https://github.com/hhuang-hep/NPS2023_Simulation)

---

## 1. Environment Setup (ifarm / JLab)

```bash
module purge
module use /group/halla/modulefiles
module load geant4/11.2.1
module load root/6.30.04
```

SIMC must also be built and available (see below).

---

## 2. External Dependencies

### NPS_SOFT (Clustering and Trigger Libraries)

```bash
cd NPS_SOFT
make biglib
```

This builds the calorimeter clustering, trigger, and reconstruction libraries.

### HallC_NPS Geant4 (DVCS Application)

```bash
cd HallC_NPS/DVCS_evt_gen/DVCS
mkdir -p build
cd build
cmake -DNPS_SOFT_ROOT=../../../NPS_SOFT ..
make
```

### SIMC

Official repository:

[https://github.com/JeffersonLab/simc_gfortran](https://github.com/JeffersonLab/simc_gfortran)

For Geant4 integration, several interface files are modified. A validated working version is available on ifarm:

```
/u/group/nps/singhav/simc_gfortran_updated
```

You may either clone this directory or apply the same modifications to your local SIMC build.

---

## 3. Running the Simulation

First generate a SIMC ROOT file for the desired kinematics.

Then run Geant4 from:

```bash
cd HallC_NPS/DVCS_evt_gen/DVCS/build
./DVCS <simc.root> [tree] [nEvents] [out.root] [--batch] [--vis|--vis-single|--vis-seq]
```

Arguments:

* `simc.root` : SIMC output file
* `tree`      : Tree name (default: `h10`)
* `nEvents`   : Number of events to process (≤ number in SIMC file)
* `out.root`  : Output ROOT file (default: `geant_output.root`)
* `--batch`   : Batch mode (recommended for production)
* `--vis`         : Start visualization UI and prepare the scene (manual stepping)
* `--vis-single`  : Start visualization UI and auto-run one event
* `--vis-seq`     : Start visualization UI in sequential stepping mode

---

## 4. KinC List and Run Selection

At startup, the program reads the Hall C kinematic list:

```
../../../../KinC_list.txt
```

It prints a concise table:

```
Run   | Kinematics
----------------------------
3241  | Ebeam=10.6 GeV, Q2=2.5, xB=0.36, ...
3242  | Ebeam=10.6 GeV, Q2=3.0, xB=0.42, ...
...
```

You are prompted to enter a run number. The corresponding configuration is automatically applied to:

* Beam energy
* HMS angle and momentum
* Calorimeter distance and orientation
* Target properties
* Magnetic field settings

This ensures full consistency between SIMC generation and Geant4 geometry.

---

## 5. Output Structure

The output ROOT file contains all original SIMC branches plus Geant4 truth and reconstruction information.

### Event-level

1. `evtNb`
   Event number

2. `edep[1080]`
   Energy deposited per calorimeter block (MeV, after 4% compensation)

### Primary photon truth

3. `phot1_hit`
   Flag indicating whether the primary photon reached the calorimeter

4. `phot1_v{x,y,z}`
   Generation vertex (SIMC)

5. `phot1_hit_{x,y,z}`
   True impact point on calorimeter front face (Geant4)

6. `phot1_Ecal`
   Total energy deposited by the primary photon shower and all secondaries (GeV)

7. `phot1_clustSize`
   Size of the reconstructed cluster associated with this photon

### Cluster reconstruction (NPS_SOFT)

8. `nClusters`
   Number of reconstructed clusters

9. `clust_E[]`
   Cluster energies (GeV)

10. `clust_X[], clust_Y[]`
    Cluster positions on calorimeter face (cm)

11. `clust_Size[]`
    Number of blocks per cluster

**Important distinction**

* `phot1_Ecal` is truth-matched energy from the primary photon shower only.
* `clust_E[i]` is reconstructed cluster energy using calorimeter blocks and trigger logic, with no knowledge of particle ancestry.
  Differences arise due to overlaps, pileup, leakage, and secondary contamination.

---

## 6. Coordinate System

The simulation uses the standard Geant4 right-handed coordinate system:

* z: downstream (beam direction)
* x: beam left
* y: upward

Care must be taken when comparing with Hall C data coordinate conventions.

---

## 7. Visualization

The DVCS application now supports three explicit visualization modes:

```bash
# Open detector view, then step manually
./DVCS simc.root h10 100 vis.root --vis

# Auto-run one event and stop in UI
./DVCS simc.root h10 1 vis.root --vis-single

# Prepare sequential viewing in UI
./DVCS simc.root h10 100 vis.root --vis-seq
```

Inside the Geant4 UI, sequential event stepping is done with:

```text
/run/beamOn 1
```

This command can be repeated to inspect events one-by-one without restarting the application.

Macro files copied to `build/macros/`:

* `vis_setup.mac`      : scene setup only
* `vis_single.mac`     : setup + one event
* `vis_sequential.mac` : setup + sequential stepping guidance
* `vis.mac`            : backward-compatible alias to `vis_setup.mac`

---

## 8. April 2026 Compatibility Update

The HallC_NPS legacy variants (glass, Energy Resolution, PbWO4) were updated for
Geant4 11 compatibility in their hit classes.

### What was fixed

Geant4 11 rejects numeric initialization of G4String fields (for example
`fOP_String(-1)`). These were updated to string initialization (`fOP_String("-1")`)
in all affected hit constructors across:

* `HallC_NPS/glass_prototype/source/src/*Hit.cc`
* `HallC_NPS/jlab_HallC_NPS_Energy_Resolution_Simulation/source/src/*Hit.cc`
* `HallC_NPS/jlab_HallC_NPS_PbWO4/source/src/*Hit.cc`

### Scope note

No source changes were made under `NPS_SOFT/`.

---

## 9. Rebuild Instructions (After This Update)

Yes, you should compile again to apply the code changes.

### Minimum rebuild (only what you run)

If you only run DVCS, rebuild DVCS:

```bash
module purge
module use /group/halla/modulefiles
module load geant4/11.2.1
module load root/6.30.04

cd HallC_NPS/DVCS_evt_gen/DVCS/build
cmake -DNPS_SOFT_ROOT=../../../NPS_SOFT ..
cmake --build . -j 8
```

If you use one of the legacy apps, rebuild that app as well:

```bash
# glass
cd HallC_NPS/glass_prototype/source
mkdir -p build && cd build
cmake ..
cmake --build . -j 8

# energy resolution
cd HallC_NPS/jlab_HallC_NPS_Energy_Resolution_Simulation/source
mkdir -p build && cd build
cmake ..
cmake --build . -j 8

# PbWO4
cd HallC_NPS/jlab_HallC_NPS_PbWO4/source
mkdir -p build && cd build
cmake ..
cmake --build . -j 8
```

### Recommended full refresh (safest)

If you want a clean state for all HallC_NPS targets:

```bash
module purge
module use /group/halla/modulefiles
module load geant4/11.2.1
module load root/6.30.04

rm -rf HallC_NPS/DVCS_evt_gen/DVCS/build
rm -rf HallC_NPS/glass_prototype/source/build
rm -rf HallC_NPS/jlab_HallC_NPS_Energy_Resolution_Simulation/source/build
rm -rf HallC_NPS/jlab_HallC_NPS_PbWO4/source/build

mkdir -p HallC_NPS/DVCS_evt_gen/DVCS/build
mkdir -p HallC_NPS/glass_prototype/source/build
mkdir -p HallC_NPS/jlab_HallC_NPS_Energy_Resolution_Simulation/source/build
mkdir -p HallC_NPS/jlab_HallC_NPS_PbWO4/source/build
```

Then configure/build each target using the commands above.

---

## 10. Quick Post-Build Checks

After rebuilding:

1. Verify executables exist:
   * `HallC_NPS/DVCS_evt_gen/DVCS/build/DVCS`
   * `HallC_NPS/glass_prototype/source/build/glass`
   * `HallC_NPS/jlab_HallC_NPS_Energy_Resolution_Simulation/source/build/NPS_Energy_Resolution`
   * `HallC_NPS/jlab_HallC_NPS_PbWO4/source/build/NPS`
2. Verify DVCS visualization modes:
   * `--vis`
   * `--vis-single`
   * `--vis-seq`
3. In UI, step sequentially with:
   * `/run/beamOn 1`

---

## 11. Contact

**Avnish Singh**
The Catholic University of America
Jefferson Lab Hall C / NPS

[singhav@cua.edu](mailto:singhav@cua.edu)
[singhav@jlab.org](mailto:singhav@jlab.org)
