#!/bin/bash -x
# Run EDM4hep conversion on a file of the dataset sh_qqps_b94_2l_c2/C1 

set -x

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Get the project root directory (parent of scripts)
PROJECT_DIR="$(dirname "${SCRIPT_DIR}")"

# Path to DELPHI data file
DATA_FILE="/eos/experiment/delphi/castor2015/tape/Y10638/Y10638.1.al"

# Output file for EDM4hep conversion
OUTPUT_FILE="${PROJECT_DIR}/output/qqps94_2l_c2.edm4hep.root"

# Create output directory if it doesn't exist
mkdir -p "${PROJECT_DIR}/output"

# Run delphi_edm4hep with the data file as input and EDM4hep output
"${PROJECT_DIR}/build/src/delphi_edm4hep" --output "${OUTPUT_FILE}" "${DATA_FILE}" "$@"
