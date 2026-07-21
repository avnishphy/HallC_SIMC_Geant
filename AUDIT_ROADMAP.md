# Repository Audit and Implementation Roadmap

# SECTION A - Full repository audit and roadmap

## 1. Executive summary

This repository appears to be a Jefferson Lab Hall C / NPS pi0 simulation chain. SIMC provides photon-level pi0 events, GEANT4 transports the photons through Hall C / NPS geometry, `NPS_SOFT` performs calorimeter trigger and clustering, and ROOT output stores merged SIMC truth plus GEANT4/NPS detector response.

The framework has a working core, sample SIMC ROOT inputs, CMake support for the active GEANT4 application, and legacy Makefile support for `NPS_SOFT`. The main risks are hard-coded paths, interactive run selection, live database dependencies, implicit SIMC branch assumptions, stale legacy files, generated artifacts mixed with source, and no automated smoke-test or validation baseline.

## 2. Repository map

- `README.md`: current top-level workflow notes, Geant4/ROOT modules, build/run examples.
- `KinC_list.txt`: run-range configuration table used at runtime.
- `HallC_NPS/`: main GEANT4 simulation area plus legacy detector examples.
- `HallC_NPS/DVCS_evt_gen/DVCS/`: active pi0/DVCS-style GEANT4 application.
- `HallC_NPS/DVCS_evt_gen/DVCS/src`, `include`: main C++ simulation, geometry, generator, event action, histogram manager.
- `HallC_NPS/DVCS_evt_gen/DVCS/*.mac`: GEANT4 batch and visualization macros.
- `HallC_NPS/draw/`: ROOT plotting and analysis macros.
- `HallC_NPS/glass_prototype/`, `jlab_HallC_NPS_*`: older or auxiliary detector studies.
- `NPS_SOFT/`: ROOT/C++ calorimeter reconstruction, clustering, database, trigger logic.
- `NPS_SOFT/initdata/`: text geometry, parameter, and calibration files, partly bypassed by DB code.

## 3. Current workflow reconstruction

1. External SIMC produces a ROOT file, usually tree `h10`, with photon branches such as `Pgamma1x/y/z`, `Egamma1`, `Pgamma2x/y/z`, `Egamma2`, and `vtx_x/y/z`.
2. User builds `NPS_SOFT` and the active `DVCS` GEANT4 executable.
3. `DVCS` reads `../../../../KinC_list.txt`, prints KinC entries, and prompts for a run number.
4. `RunConfigParser` applies beam energy, HMS/NPS angle settings, NPS distance, and run-range metadata.
5. `PrimaryGeneratorAction` reads one SIMC entry per event and creates two GEANT4 gamma primaries. Pi0 decay is not done in GEANT4; it is assumed to have happened upstream in SIMC.
6. `DetectorConstruction` builds the target, chamber, optional sweeping magnet, NPS PbWO4 calorimeter, PMT/wrapping volumes, and flux volumes.
7. `B5HadCalorimeterSD` records crystal energy deposits and photon hit metadata.
8. `EventAction` fills `TCaloEvent`, runs `TriggerSim(0.5)`, then `DoClustering(-5.0, 5.0)`.
9. `HistoManager` writes ROOT output using tree `nerd`, copying supported scalar SIMC leaves and adding GEANT4/NPS branches.
10. Standalone ROOT macros under `HallC_NPS/draw` and prototype folders perform plotting or detector-study analysis.

## 4. Component-by-component documentation

- `HallC_NPS/CMakeLists.txt`: top-level CMake entry; adds the DVCS subdirectory; accepts optional `NPS_SOFT_ROOT`.
- `HallC_NPS/DVCS_evt_gen/DVCS/CMakeLists.txt`: builds executable `DVCS`; finds Geant4 and ROOT; links optional `libDVCS` and `libTDVCSGlobal2`; copies macros into the build directory.
- `HallC_NPS/DVCS_evt_gen/DVCS/GNUmakefile`: legacy build file with old absolute paths; likely stale.
- `main.cc`: command-line parsing, KinC loading, interactive run-number prompt, GEANT4 setup, batch and visualization modes.
- `RunConfigParser`: parses `KinC_list.txt`; applies selected run-range values to global configuration.
- `dvcsGlobals`: process-wide mutable global configuration.
- `PrimaryGeneratorAction`: SIMC ROOT reader; creates two photon primaries; applies implicit coordinate and sign convention.
- `DetectorConstruction`: hard-coded Hall C/NPS geometry and materials.
- `B5HadCalorimeterSD`: NPS crystal sensitive detector; tracks photon ancestry and energy deposits.
- `EventAction`: converts GEANT4 hits to `NPS_SOFT` calorimeter blocks, triggers/clusters them, and assigns clusters to photons.
- `HistoManager`: output ROOT writer and scalar SIMC branch copier.
- `PhysicsList`: EM and decay physics by default; optical physics code exists but is disabled.
- `SimpleField`: sweeping magnet field map reader with hard-coded absolute map path.
- `NPS_SOFT/Makefile`: builds ROOT dictionaries and shared libraries; `biglib` creates the combined library.
- `NPS_SOFT/TCalo*`: calorimeter geometry, trigger, clustering, and shower reconstruction.
- `NPS_SOFT/TDVCS*`: DVCS event, geometry, and database support.
- `NPS_SOFT/TDVCSDB.cxx`: hard-coded JLab MySQL connection logic and credentials.

## 5. Hard-coded assumptions and hidden dependencies

- `DVCS` assumes the runtime current working directory lets it find `../../../../KinC_list.txt`.
- Batch mode still requires interactive run-number input unless stdin supplies it.
- Runtime needs `NPS_SOFT` in the environment; build uses separate `NPS_SOFT_ROOT`.
- The documented SIMC source/version is external to this repository.
- `NPS_SOFT` geometry/calibration may come from a live MySQL database rather than versioned local files.
- `SimpleField.cc` references an absolute field-map path under an old user/work area.
- Output ROOT files are opened with `RECREATE`, so existing outputs can be overwritten silently.
- Required SIMC branches are assumed rather than validated.
- Important constants are hard-coded: trigger threshold `0.5`, clustering window `[-5,+5]`, energy scale `1.04`, crystal pitch `2.113 cm`, default cut `0.7 mm`, target and geometry dimensions.
- The detector and reconstruction state uses static data and assumes serial execution.

## 6. Current caveats and risks

- Working tree is dirty and contains generated artifacts, so current baseline state is ambiguous.
- README build path for `NPS_SOFT_ROOT` may need verification from the documented build directory.
- Selected run number and KinC interval-begin run number may not be handled consistently.
- NPS-to-Hall rotation code exists but appears bypassed in photon generation.
- Pi0 decay handling is external and not documented as a formal interface.
- Text init files exist, but current code may use live database geometry/calibration.
- Optical material properties are defined, but optical physics is disabled.
- Photon-cluster assignment is heuristic and considers only the first two clusters for per-photon matching.
- Plotting macros use hard-coded filenames and output paths.
- Legacy docs reference ROOT 5, old Hosan paths, and old analyzer/SIMC locations.
- No small-statistics smoke test, regression baseline, provenance metadata, or validation report exists.
- Hard-coded database credentials are a security and reproducibility risk.

## 7. Improvement opportunities

### Baseline capture

- Problem: no reproducible reference behavior.
- Proposed solution: capture git status, commit, environment, build commands, sample run, ROOT branch schema, logs, and checksums.
- Likely affected files: future documentation or validation artifacts.
- Risk level: low.
- Verification method: repeat baseline commands and compare metadata.
- Success criteria: baseline can be rebuilt and rerun.
- Physics behavior unchanged: yes.

### Documentation cleanup

- Problem: workflow details are scattered and partly stale.
- Proposed solution: create one authoritative workflow guide and mark legacy notes clearly.
- Likely affected files: `README.md`, `HallC_NPS/DVCS_evt_gen/DVCS/README`, optional `docs/`.
- Risk level: low.
- Verification method: confirm commands match current code.
- Success criteria: new user can build and run a sample.
- Physics behavior unchanged: yes.

### Configuration and path cleanup

- Problem: hard-coded paths and current-working-directory assumptions.
- Proposed solution: add backward-compatible CLI/config options for KinC path, run number, input/output, field map, and output directory.
- Likely affected files: `main.cc`, `RunConfigParser.*`, `SimpleField.*`, docs.
- Risk level: medium.
- Verification method: old and new commands produce matching smoke-test output.
- Success criteria: noninteractive run works without hidden CWD assumptions.
- Physics behavior unchanged: yes, if defaults are preserved.

### SIMC interface validation

- Problem: missing branch checks can fail late or silently.
- Proposed solution: validate required branches at startup and print an input schema report.
- Likely affected files: `PrimaryGeneratorAction.*`, `HistoManager.*`.
- Risk level: low to medium.
- Verification method: good input runs; bad input fails with a clear error.
- Success criteria: SIMC incompatibilities are caught before event processing.
- Physics behavior unchanged: yes.

### Output safety and provenance

- Problem: outputs can be overwritten and lack provenance.
- Proposed solution: add overwrite protection, reproducible run folders, and metadata in ROOT or sidecar files.
- Likely affected files: `HistoManager.*`, run wrappers, docs.
- Risk level: medium.
- Verification method: output metadata exists and no-overwrite behavior works.
- Success criteria: every output can be traced to input, code version, config, and environment.
- Physics behavior unchanged: yes.

### DB/config reproducibility

- Problem: live database dependency prevents offline reproducibility.
- Proposed solution: document DB use and allow frozen text or ROOT calibration snapshots.
- Likely affected files: `NPS_SOFT/TCalo*`, `NPS_SOFT/TDVCS*`, docs.
- Risk level: high.
- Verification method: compare DB-backed and snapshot-backed output for selected runs.
- Success criteria: frozen config reproduces DB behavior within agreed tolerance.
- Physics behavior unchanged: only if validated against baseline.

### Validation suite

- Problem: no automated scientific regression checks.
- Proposed solution: add small-stat checks for pi0 invariant mass, photon directions, NPS hit maps, energy sums, cluster counts, and plot comparisons.
- Likely affected files: validation macros/scripts and docs.
- Risk level: low.
- Verification method: validation report with pass/fail thresholds.
- Success criteria: regressions are detected before large production runs.
- Physics behavior unchanged: yes, unless a later approved fix changes physics.

## 8. Concrete staged roadmap

### Stage 0 - Baseline and environment capture

Capture `git status`, commit hash, module list, ROOT/Geant4 versions, `NPS_SOFT`, exact build commands, sample SIMC input, selected run number, event count, stdout/stderr, output ROOT schema, and summary histograms. This stage preserves current behavior before edits.

### Stage 1 - Documentation and workflow clarification

Document the active workflow, SIMC input schema, `KinC_list.txt`, run-number prompt, output tree `nerd`, expected branches, DB dependency, known caveats, command examples, and troubleshooting.

### Stage 2 - Configuration and path cleanup

Add backward-compatible CLI/config support for run number, KinC path, output directory, field map, no-overwrite behavior, and runtime `NPS_SOFT`. Preserve existing defaults.

### Stage 3 - Modularization

Separate SIMC reading, configuration loading, output/provenance, and validation helpers from monolithic event/action code. Keep backward-compatible wrappers.

### Stage 4 - Physics and geometry validation

Add checks for pi0 invariant mass, photon directions, NPS geometry dimensions, 1080-block mapping, trigger/clustering rates, energy sums, and DB/text geometry differences.

### Stage 5 - Automated checks and reproducibility

Add a smoke-test driver, ROOT schema checker, macro syntax checks, log checks, baseline comparison, and reproducible run directories.

### Stage 6 - Final user-facing framework documentation

Produce installation, setup, build, run, analysis, plotting, validation, troubleshooting, examples, and developer documentation.

## 9. Validation strategy

- Build checks: `make biglib` for `NPS_SOFT`; CMake build for `DVCS`.
- Smoke run: small event count from an existing sample SIMC ROOT file with fixed run number.
- ROOT schema check: confirm tree `nerd`, scalar SIMC leaves, `edep[1080]`, photon hit/cluster branches, and cluster vectors.
- Physics checks: pi0 invariant mass from SIMC photons, vertex distribution, photon energy conservation, NPS hit occupancy, and cluster energy sums.
- Geometry checks: 30x36 blocks, NPS distance/angle from KinC, target material/length, and DB geometry values.
- Plot checks: stable summary plots compared to baseline images or ROOT histograms.
- Log checks: detect missing branches, DB fallback, field-map load failure, and overwrite warnings.
- Baseline comparisons: branch lists, event counts, scalar summaries, and histograms with tolerances.

## 10. Questions and unknowns

- Which SIMC repository/version is authoritative for current pi0 production?
- Should `NPS_SOFT` use live DB geometry/calibration or frozen local snapshots?
- Is the bypassed NPS-to-Hall rotation intentional?
- Should the exact selected run number or KinC interval-begin run number be used for DB/reconstruction?
- Is optical photon simulation intentionally disabled?
- What sample input/run should define the official smoke baseline?
- Are prototype directories still maintained or archival?
- Which plotting macros are part of the official analysis chain?

## 11. Approval gate

I will not make any code changes until you explicitly approve the implementation plan.

# SECTION B - Compact Gemma 4 31B implementation packet

Repository path: `/w/hallc-scshelf2102/nps/singhav/geant4_simc`

Current structure:

- `README.md`: current but incomplete workflow.
- `KinC_list.txt`: run-range beam/HMS/NPS configuration.
- `HallC_NPS/DVCS_evt_gen/DVCS/`: active GEANT4 app.
- `HallC_NPS/DVCS_evt_gen/DVCS/src`, `include`: core C++.
- `NPS_SOFT/`: ROOT/C++ calorimeter trigger, clustering, and DB support.
- `HallC_NPS/draw/`, `glass_prototype/draw/`: ROOT plotting macros.
- Generated artifacts currently exist; do not treat tree as clean.

Implementation rules:

- Do not make changes until the user approves a stage.
- Work stage by stage only.
- Preserve physics behavior unless the user explicitly approves a physics change.
- Test after every logical change.
- Never claim success without verification.
- Report modified files, commands run, tests passed/failed, and open risks.
- Avoid destructive commands.
- Do not delete generated files unless explicitly instructed.

Approved roadmap:

1. Stage 0: capture baseline and environment.
2. Stage 1: clarify documentation.
3. Stage 2: clean config/path handling with backward-compatible defaults.
4. Stage 3: modularize simulation, SIMC interface, output, and plotting utilities.
5. Stage 4: add physics/geometry validation.
6. Stage 5: add smoke tests and reproducibility checks.
7. Stage 6: finalize user/developer documentation.

Likely files touched after approval:

- `README.md`
- `HallC_NPS/DVCS_evt_gen/DVCS/README`
- `HallC_NPS/DVCS_evt_gen/DVCS/src/main.cc`
- `HallC_NPS/DVCS_evt_gen/DVCS/src/RunConfigParser.cc`
- `HallC_NPS/DVCS_evt_gen/DVCS/include/RunConfigParser.hh`
- `HallC_NPS/DVCS_evt_gen/DVCS/src/PrimaryGeneratorAction.cc`
- `HallC_NPS/DVCS_evt_gen/DVCS/include/PrimaryGeneratorAction.hh`
- `HallC_NPS/DVCS_evt_gen/DVCS/src/HistoManager.cc`
- `HallC_NPS/DVCS_evt_gen/DVCS/include/HistoManager.hh`
- `HallC_NPS/DVCS_evt_gen/DVCS/src/SimpleField.cc`
- selected validation, plotting, or documentation files

Verification strategy:

- Capture `git status`, commit, module list, ROOT/Geant4 versions.
- Build `NPS_SOFT` and `DVCS`.
- Run a tiny fixed-event sample using an existing SIMC ROOT file and selected KinC run.
- Check output ROOT tree `nerd` branch schema.
- Compare event count, energy summaries, cluster counts, hit occupancy, and pi0 invariant mass.
- Record logs and failures.

Success criteria:

- Existing workflow remains runnable.
- New docs match real commands.
- New config options remove hidden CWD/path assumptions without breaking old defaults.
- Smoke test gives stable output.
- Validation identifies physics/geometry regressions before larger runs.

Reporting format:

- Stage completed.
- Files changed.
- Commands run.
- Verification results.
- Physics behavior changed: yes/no.
- Open risks/questions.

Begin with the approved stage only. Do not implement later stages until instructed.
