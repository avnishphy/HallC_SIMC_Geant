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
./DVCS <simc.root> [tree] [nEvents] [out.root] [--batch] [--vis]
```

Arguments:

* `simc.root` : SIMC output file
* `tree`      : Tree name (default: `h10`)
* `nEvents`   : Number of events to process (≤ number in SIMC file)
* `out.root`  : Output ROOT file (default: `geant_output.root`)
* `--batch`   : Batch mode (recommended for production)
* `--vis`     : Geant4 visualization (currently reliable for single-event runs)

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

Single-event visualization:

```bash
./DVCS simc.root h10 1 vis.root --vis
```

Displays:

* NPS crystal geometry
* Electromagnetic shower development
* Primary photon trajectories
* Energy deposition patterns

---

## 8. Contact

**Avnish Singh**
The Catholic University of America
Jefferson Lab Hall C / NPS

[singhav@cua.edu](mailto:singhav@cua.edu)
[singhav@jlab.org](mailto:singhav@jlab.org)
