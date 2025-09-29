#!/bin/bash -x
# Run on a file of the dataset sh_qqps_b94_2l_c2/C1 

set -x

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Get the project root directory (parent of scripts)
PROJECT_DIR="$(dirname "${SCRIPT_DIR}")"

# Path to DELPHI data file
DATA_FILE="/eos/experiment/delphi/castor2015/tape/Y10638/Y10638.1.al"

# Run delphi_phdst with the data file as input (using absolute path)
"${PROJECT_DIR}/build/src/delphi_phdst" "${DATA_FILE}" "$@"
