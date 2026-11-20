# Exclusive / SIDIS π⁰ Geant4 + SIMC Reconstruction Framework

This repository contains a Geant4-based detector simulation and reconstruction framework for exclusive and SIDIS π⁰ reactions in Hall C. It interfaces directly with SIMC ROOT output, propagates generated particles through a realistic NPS calorimeter and spectrometer geometry, performs clustering and trigger emulation, and writes analysis-ready ROOT ntuples.

The framework provides:

* SIMC → Geant4 event transport
* Full electromagnetic shower simulation in the NPS calorimeter
* Cluster reconstruction and trigger response using NPS_SOFT
* Event-by-event truth association of primary photons with deposited energy
* User-selectable kinematic configuration from the shared simulation CSV
  (default) or legacy Hall C `KinC_list.txt`

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
cmake -DNPS_SOFT_ROOT=../../../../NPS_SOFT ..
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
./DVCS <simc.root> [tree] [nEvents] [out.root] [--batch] \
  [--vis|--vis-single|--vis-seq] \
  [--config-source csv|kinc] [--config-file PATH] [--run RUN]
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
* `--config-source` : Select `csv` or legacy `kinc`; omitted means prompt
* `--config-file` : Override the selected source path
* `--run`         : Select the run without the run-number prompt

---

## 4. Kinematic Configuration and Run Selection

At startup, the program asks which configuration to use:

```text
Select kinematic configuration source:
  1. nps_simulation_kinematics.csv [default]
  2. KinC_list.txt (legacy)
Selection [1]:
```

The shared CSV is authoritative for current simulation production:

```text
../nps_analysis/pi0_analysis/root_analysis_env_main/config/nps_simulation_kinematics.csv
```

Override this location when needed:

```bash
export NPS_SIMULATION_KINEMATICS_CSV=/path/to/nps_simulation_kinematics.csv
# or
./DVCS input.root h10 100 output.root --batch \
  --config-source csv --config-file /path/to/file.csv --run 2976
```

CSV selection uses exact `source_run`. Applied fields are `ebeam_gev`,
`hms_p_gev`, `hms_theta_deg`, `nps_theta_deg`,
`nps_target_distance_cm`, and `target`. Current CSV rows use `LH2`.

Legacy `KinC_list.txt` remains supported. Its match is inclusive:
`begin_run <= selected_run <= end_run`. The exact selected run—not interval
start—is passed to `NPS_SOFT` for run-dependent database lookup.

Neither source currently controls target length, target offsets, sweeping-field
enable/strength, detector dimensions, trigger threshold, clustering window, or
energy scale. Those remain code/runtime settings. The program prints selected
values before Geant4 initialization; verify they match the SIMC infile.

For prompt-free local execution, provide both `--config-source` and `--run`.

---

## 5. Output Structure

The output ROOT file contains all original SIMC branches plus Geant4 truth and reconstruction information.

### Event-level

1. `evtNb`
   Event number

2. `edep[1080]`
   Corrected energy per calorimeter block in MeV: raw Geant4 deposit × `1.04`

### Primary photon truth

3. `phot1_hit`
   Flag indicating whether the primary photon reached the calorimeter

4. `phot1_v{x,y,z}`
   Generation vertex (SIMC)

5. `phot1_hit_{x,y,z}`
   True impact point on calorimeter front face (Geant4)

6. `phot1_Ecal`
   Raw Geant4 energy deposited by the primary photon shower and descendants
   (GeV); the `1.04` scale is not applied

7. `phot1_clustSize`
   Size of the reconstructed cluster associated with this photon

### Cluster reconstruction (NPS_SOFT)

8. `nClusters`
   Number of reconstructed clusters

9. `clust_E[]`
   Cluster energies (GeV), reconstructed from block energies after the `1.04`
   scale

10. `clust_X[], clust_Y[]`
    Cluster positions on calorimeter face (cm)

11. `clust_Size[]`
    Number of blocks per cluster

**Important distinction**

* `phot1_Ecal` is truth-matched energy from the primary photon shower only.
* `clust_E[i]` is reconstructed cluster energy using calorimeter blocks and trigger logic, with no knowledge of particle ancestry.
  Differences arise due to overlaps, pileup, leakage, and secondary contamination.

### 4% calorimeter energy scale

`EventAction` defines one named scale, `kCaloEnergyScale = 1.04`. It is applied
to each raw crystal deposit before filling `edep[1080]` and before passing block
energies to `TCaloEvent`. Therefore `clust_E[]` and `TriggerSim(0.5 GeV)` use
corrected energies. The 0.5 GeV corrected trigger threshold corresponds to
approximately 0.4808 GeV raw deposit. Original SIMC photon branches and
`phot1_Ecal`/`phot2_Ecal` remain unscaled. This is retained historical NPS
reconstruction compensation; no derivation is stored in this repository.

---

## 6. Coordinate System

The simulation uses the standard Geant4 right-handed coordinate system:

* z: downstream (beam direction)
* x: beam left
* y: upward

Care must be taken when comparing with Hall C data coordinate conventions.

NPS contains 30 rows × 36 columns. `DetectorConstruction` is authoritative for
crystal pitch:

```text
pitch = crystal + 2*wrapper + gap
      = 20.5 mm + 2*0.095 mm + 1.0 mm
      = 21.69 mm
```

The same runtime pitch now defines `phot{1,2}_hit_x/y`. For row `r`, column `c`,
and crystal-local hit `(localX, localY)`:

```text
hitX = (14.5 - r) * pitchX + localX
hitY = (c - 17.5) * pitchY + localY
```

Coordinates are written in cm. Changing crystal size, wrapper thickness, or gap
in `DetectorConstruction` automatically changes both placement and truth-hit
coordinates; no independent pitch constant exists in `EventAction`.

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
cmake -DNPS_SOFT_ROOT=../../../../NPS_SOFT ..
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

## 11. SWIF2 Batch Submission

`submit_geant4_swif2.sh` creates one independent job per selected SIMC ROOT
file. It supports all 33 CSV kinematics, any single legacy token such as
`x36_2p`, all three channels, or one channel.

```bash
# All 33 kinematics × all 3 channels = 99 jobs
./submit_geant4_swif2.sh

# One kinematic, all channels = 3 jobs
./submit_geant4_swif2.sh --kin x36_2p

# All kinematics, exclusive only = 33 jobs
./submit_geant4_swif2.sh --channel excl

# One exact input/job
./submit_geant4_swif2.sh --kin x36_2p --channel delta
```

Default inputs:

```text
/w/hallc-scshelf2102/nps/singhav/nps_analysis/pi0_analysis/
  root_analysis_env_main/output/simc/nps_simc_20260824_135058/
  worksim/simc_gfortran_updated/worksim/nps_<channel>_pi0_<kin>.root
```

Override this production directory with `--input-dir DIR` when using a newer
SIMC workflow.

Kinematic-to-run mapping comes from `nps_simulation_kinematics.csv`; each job
passes the row's exact `source_run` to DVCS. Missing expected inputs abort before
workflow creation, so an `all` request cannot silently submit a partial set.

The submit host performs a fresh Release build in `/tmp`, then packages only the
DVCS executable, NPS_SOFT shared libraries/ROOT dictionaries/initdata, exact CSV
snapshot, and build provenance. It validates gzip integrity, required archive
members, and shared-library resolution. Workers unpack this tar and do not
compile.

Defaults:

* Runtime tar: `/group/nps/$USER/swif_inputs/<workflow>_geant4_runtime.tar.gz`
* ROOT output: `/volatile/hallc/nps/$USER/geant4_simc/<workflow>/<channel>/nps_<channel>_pi0_<kin>_geant4.root`
* Logs: `/farm_out/$USER/geant4_simc/<workflow>/`
* Resources: one core, 4 GB RAM, 12 GB scratch, 24 hours

The 12 GB scratch request covers staged SIMC input plus potentially large
`edep[1080]` output for up to one million events; override with `--disk` after
measuring smaller production outputs.

Each ROOT output has an exact SWIF output mapping—no wildcard and no output tar.
Worker validation requires a nonempty ROOT file containing tree `nerd`.

Useful overrides:

```bash
./submit_geant4_swif2.sh --workflow test_x36_2p \
  --kin x36_2p --channel all --events 1000 \
  --output-dir /volatile/hallc/nps/$USER/geant4_simc/test_x36_2p

# Build runtime, verify all requested inputs, and count jobs without SWIF changes
./submit_geant4_swif2.sh --dry-run
```

See `./submit_geant4_swif2.sh --help` for path, tree, tar, and resource options.

## 12. Contact

**Avnish Singh**
The Catholic University of America
Jefferson Lab Hall C / NPS

[singhav@cua.edu](mailto:singhav@cua.edu)
[singhav@jlab.org](mailto:singhav@jlab.org)


### Sweeping-magnet shadow with the field off

Append `--sweeper-material 4` to a DVCS invocation to transport through the
installed sweep magnet at a +4 degree angle relative to the NPS arm. The
placement follows the configured NPS angle. This option models passive material
with the existing field-off SIMC workflow. Select the relative angle for the
hardware setting being studied. Omit the option to reproduce the previous
field-off geometry. An explicit angle of zero places the magnet aligned with
the arm. Check the startup summary for material placement, field and angle.
