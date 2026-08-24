#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SELF="${SCRIPT_DIR}/$(basename "${BASH_SOURCE[0]}")"
DVCS_SOURCE="${SCRIPT_DIR}/HallC_NPS/DVCS_evt_gen/DVCS"
NPS_SOFT_DIR="${SCRIPT_DIR}/NPS_SOFT"
ANALYSIS_ROOT="/w/hallc-scshelf2102/nps/singhav/nps_analysis/pi0_analysis/root_analysis_env_main"
DEFAULT_INPUT_DIR="${ANALYSIS_ROOT}/output/simc/nps_simc_20260824_135058/worksim/simc_gfortran_updated/worksim"
DEFAULT_CONFIG="${ANALYSIS_ROOT}/config/nps_simulation_kinematics.csv"

load_environment() {
  if ! type module >/dev/null 2>&1; then
    # Batch shells may not initialize Environment Modules automatically.
    source /usr/share/Modules/init/bash
  fi
  module purge
  module use /group/halla/modulefiles
  module load geant4/11.2.1
  module load root/6.30.04
}

# Worker mode: SWIF stages one SIMC file, one runtime tar, and this script.
if [[ "${1:-}" == "--run-one" ]]; then
  runtime_tar="${PWD}/$2"
  simc_file="${PWD}/$3"
  run_number="$4"
  events="$5"
  tree_name="$6"
  output_file="${PWD}/$7"

  tar -xzf "${runtime_tar}" -C "${PWD}"
  runtime="${PWD}/geant4_runtime"
  [[ -x "${runtime}/bin/DVCS" ]] || { echo "Runtime missing DVCS executable" >&2; exit 20; }
  [[ -s "${simc_file}" ]] || { echo "Missing SIMC input: ${simc_file}" >&2; exit 21; }

  load_environment
  export NPS_SOFT="${runtime}/NPS_SOFT"
  export LD_LIBRARY_PATH="${NPS_SOFT}:${LD_LIBRARY_PATH:-}"

  "${runtime}/bin/DVCS" "${simc_file}" "${tree_name}" "${events}" "${output_file}" \
    --batch --config-source csv \
    --config-file "${runtime}/config/nps_simulation_kinematics.csv" \
    --run "${run_number}"

  [[ -s "${output_file}" ]] || { echo "DVCS produced no ROOT output" >&2; exit 22; }
  root_listing="$(rootls -t "${output_file}")"
  grep -qE '^TTree .* nerd;' <<< "${root_listing}" || {
    echo "ROOT output missing tree nerd" >&2; exit 23;
  }
  exit 0
fi

usage() {
  cat <<'EOF'
Usage: submit_geant4_swif2.sh [options]

  --kin all|KIN          All kinematics or one token, e.g. x36_2p (default: all)
  --channel all|CHANNEL  all, excl, delta, or sidis (default: all)
  --workflow NAME        SWIF workflow name (default: timestamped)
  --input-dir DIR        SIMC ROOT directory
  --config FILE          nps_simulation_kinematics.csv path
  --output-dir DIR       Final output base; channel subdirectories are created
  --events N             Events per input; -1 means all (default: -1)
  --tree NAME            SIMC tree name (default: h10)
  --tar FILE             Runtime tar destination
  --ram SIZE             Per-job RAM (default: 4g)
  --disk SIZE            Per-job scratch (default: 12g)
  --time TIME            Per-job limit (default: 24h)
  --dry-run              Build/validate tar and selection; do not create workflow
EOF
}

workflow="nps_geant4_$(date +%Y%m%d_%H%M%S)"
kin_arg="all"
channel_arg="all"
input_dir="${DEFAULT_INPUT_DIR}"
config_file="${DEFAULT_CONFIG}"
output_dir=""
runtime_tar=""
events="-1"
tree_name="h10"
ram="4g"
disk="12g"
time_limit="24h"
dry_run=0

while [[ $# -gt 0 ]]; do
  case "$1" in
    --workflow) workflow="$2"; shift 2 ;;
    --kin) kin_arg="$2"; shift 2 ;;
    --channel) channel_arg="${2,,}"; shift 2 ;;
    --input-dir) input_dir="$2"; shift 2 ;;
    --config) config_file="$2"; shift 2 ;;
    --output-dir) output_dir="$2"; shift 2 ;;
    --events) events="$2"; shift 2 ;;
    --tree) tree_name="$2"; shift 2 ;;
    --tar) runtime_tar="$2"; shift 2 ;;
    --ram) ram="$2"; shift 2 ;;
    --disk) disk="$2"; shift 2 ;;
    --time) time_limit="$2"; shift 2 ;;
    --dry-run) dry_run=1; shift ;;
    -h|--help) usage; exit 0 ;;
    *) echo "Unknown option: $1" >&2; usage >&2; exit 2 ;;
  esac
done

[[ "${workflow}" =~ ^[A-Za-z0-9][A-Za-z0-9_-]*$ ]] || {
  echo "Invalid workflow name: ${workflow}" >&2; exit 2;
}
[[ "${events}" =~ ^(-1|[1-9][0-9]*)$ ]] || {
  echo "--events must be -1 or a positive integer" >&2; exit 2;
}
[[ -d "${input_dir}" ]] || { echo "Missing input directory: ${input_dir}" >&2; exit 3; }
[[ -f "${config_file}" ]] || { echo "Missing config CSV: ${config_file}" >&2; exit 3; }
input_dir="$(readlink -f "${input_dir}")"
config_file="$(readlink -f "${config_file}")"
output_dir="$(readlink -m "${output_dir:-/volatile/hallc/nps/${USER}/geant4_simc/${workflow}}")"
runtime_tar="$(readlink -m "${runtime_tar:-/group/nps/${USER}/swif_inputs/${workflow}_geant4_runtime.tar.gz}")"
log_dir="/farm_out/${USER}/geant4_simc/${workflow}"

case "${channel_arg}" in
  all) channels=(excl delta sidis) ;;
  excl|delta|sidis) channels=("${channel_arg}") ;;
  *) echo "Unknown channel: ${channel_arg}" >&2; exit 2 ;;
esac

# Map filename kinematic tokens to exact CSV source runs. Commas inside later
# quoted fields cannot affect columns 2 and 23 used here.
declare -A run_for_kin
all_kins=()
while IFS=, read -r kin_old source_run; do
  kin_old="${kin_old//[[:space:]]/}"
  source_run="${source_run//[[:space:]]/}"
  kin_old="${kin_old#KinC_}"
  [[ -n "${kin_old}" && "${source_run}" =~ ^[0-9]+$ ]] || continue
  [[ -z "${run_for_kin[${kin_old}]:-}" ]] || {
    echo "Duplicate CSV kinematic: ${kin_old}" >&2; exit 4;
  }
  run_for_kin["${kin_old}"]="${source_run}"
  all_kins+=("${kin_old}")
done < <(tail -n +2 "${config_file}" | cut -d, -f2,23)
[[ ${#all_kins[@]} -gt 0 ]] || { echo "No kinematics parsed from ${config_file}" >&2; exit 4; }

kin_arg="${kin_arg#KinC_}"
if [[ "${kin_arg}" == "all" ]]; then
  selected_kins=("${all_kins[@]}")
elif [[ -n "${run_for_kin[${kin_arg}]:-}" ]]; then
  selected_kins=("${kin_arg}")
else
  echo "Kinematic '${kin_arg}' not found in ${config_file}" >&2
  exit 4
fi

# Resolve every input/output before creating tar or workflow. All-mode fails
# atomically if any expected channel/kinematic input is absent.
job_names=()
job_inputs=()
job_runs=()
job_channels=()
job_outputs=()
for kin in "${selected_kins[@]}"; do
  for channel in "${channels[@]}"; do
    base="nps_${channel}_pi0_${kin}"
    input="${input_dir}/${base}.root"
    [[ -s "${input}" ]] || { echo "Missing SIMC input: ${input}" >&2; exit 5; }
    job_names+=("geant4_${channel}_${kin}")
    job_inputs+=("${input}")
    job_runs+=("${run_for_kin[${kin}]}")
    job_channels+=("${channel}")
    job_outputs+=("${output_dir}/${channel}/${base}_geant4.root")
  done
done

mkdir -p "$(dirname "${runtime_tar}")"
(( dry_run )) || mkdir -p "${log_dir}"
for channel in "${channels[@]}"; do mkdir -p "${output_dir}/${channel}"; done

# Build once on submit host. Worker jobs unpack this verified runtime; no worker
# compilation and no 1.4 GB build-tree archive.
tmp_dir="$(mktemp -d /tmp/nps_geant4_swif.XXXXXX)"
tar_tmp="${runtime_tar}.tmp.$$"
cleanup() {
  if [[ "${tmp_dir}" == /tmp/nps_geant4_swif.* && -d "${tmp_dir}" ]]; then
    rm -rf -- "${tmp_dir}"
  fi
  if [[ -f "${tar_tmp}" ]]; then
    rm -f -- "${tar_tmp}"
  fi
  return 0
}
trap cleanup EXIT

load_environment
cmake -S "${DVCS_SOURCE}" -B "${tmp_dir}/build" \
  -DNPS_SOFT_ROOT="${NPS_SOFT_DIR}" -DCMAKE_BUILD_TYPE=Release
cmake --build "${tmp_dir}/build" --parallel "${NPS_GEANT4_BUILD_JOBS:-8}"

runtime="${tmp_dir}/geant4_runtime"
mkdir -p "${runtime}/bin" "${runtime}/NPS_SOFT" "${runtime}/config"
cp "${tmp_dir}/build/DVCS" "${runtime}/bin/"
cp "${NPS_SOFT_DIR}"/*.so "${runtime}/NPS_SOFT/"
cp "${NPS_SOFT_DIR}"/*_rdict.pcm "${runtime}/NPS_SOFT/"
cp -a "${NPS_SOFT_DIR}/initdata" "${runtime}/NPS_SOFT/"
cp "${config_file}" "${runtime}/config/nps_simulation_kinematics.csv"
git_dirty=no
[[ -z "$(git -C "${SCRIPT_DIR}" status --porcelain)" ]] || git_dirty=yes
printf 'built_utc=%s\ngit_commit=%s\ngit_dirty=%s\n' \
  "$(date -u +%Y-%m-%dT%H:%M:%SZ)" \
  "$(git -C "${SCRIPT_DIR}" rev-parse HEAD)" \
  "${git_dirty}" \
  > "${runtime}/BUILD_INFO.txt"

if LD_LIBRARY_PATH="${runtime}/NPS_SOFT:${LD_LIBRARY_PATH:-}" \
   ldd "${runtime}/bin/DVCS" | grep -q 'not found'; then
  echo "Runtime executable has unresolved shared libraries" >&2
  LD_LIBRARY_PATH="${runtime}/NPS_SOFT:${LD_LIBRARY_PATH:-}" ldd "${runtime}/bin/DVCS" >&2
  exit 6
fi

tar -C "${tmp_dir}" -czf "${tar_tmp}" geant4_runtime
gzip -t "${tar_tmp}"
tar_contents="$(tar -tzf "${tar_tmp}")"
for required in \
  geant4_runtime/bin/DVCS \
  geant4_runtime/NPS_SOFT/libDVCS.so \
  geant4_runtime/NPS_SOFT/libTDVCSGlobal2.so \
  geant4_runtime/NPS_SOFT/initdata/calogeom.txt \
  geant4_runtime/config/nps_simulation_kinematics.csv; do
  grep -Fxq "${required}" <<< "${tar_contents}" || {
    echo "Runtime tar missing ${required}" >&2; exit 6;
  }
done
mv -f "${tar_tmp}" "${runtime_tar}"
sha256sum "${runtime_tar}" > "${runtime_tar}.sha256"

echo "Runtime: ${runtime_tar}"
echo "Jobs: ${#job_names[@]} (${#selected_kins[@]} kinematics x ${#channels[@]} channels)"
echo "Outputs: ${output_dir}/{${channels[*]}}"
if (( dry_run )); then
  echo "Dry run complete; workflow not created."
  exit 0
fi

swif2 create "${workflow}"
for i in "${!job_names[@]}"; do
  swif2 add-job "${workflow}" \
    -name "${job_names[$i]}" -account hallc -partition production \
    -cores 1 -ram "${ram}" -disk "${disk}" -time "${time_limit}" \
    -stdout "${log_dir}/${job_names[$i]}.out" \
    -stderr "${log_dir}/${job_names[$i]}.err" \
    -input geant4_runtime.tar.gz "file:${runtime_tar}" \
    -input simc_input.root "file:${job_inputs[$i]}" \
    -input submit_geant4_swif2.sh "file:${SELF}" \
    -output geant_output.root "file:${job_outputs[$i]}" \
    /bin/bash submit_geant4_swif2.sh --run-one \
      geant4_runtime.tar.gz simc_input.root "${job_runs[$i]}" \
      "${events}" "${tree_name}" geant_output.root
done

swif2 run "${workflow}"
echo "Submitted ${#job_names[@]} jobs: ${workflow}"
echo "Logs: ${log_dir}"
