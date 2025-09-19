#!/bin/bash -x
set -euo pipefail

# Find the directory of this script (resolves symlinks too)
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
REPO_ROOT="$( cd -- "$SCRIPT_DIR/.." &> /dev/null && pwd )"

WORK_DIR="/afs/cern.ch/work/${USER:0:1}/${USER}/delphi-edm4hep"
mkdir -p "$WORK_DIR"
cd "$WORK_DIR" || exit 1

"$REPO_ROOT/build/src/delphi-edm4hep" \
     -c "$REPO_ROOT/config/delphi-edm4hep.yaml" \
     -o "test-edm4hep.root" \
     -m 100 \
     -i /eos/experiment/delphi/castor2015/tape/Y13709/Y13709.1.al
