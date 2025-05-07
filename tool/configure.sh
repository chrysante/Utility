#!/bin/bash

set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJ_DIR=$SCRIPT_DIR/..

cmake -S "$PROJ_DIR" -B "$PROJ_DIR/build" -DCPM_SOURCE_CACHE=.cache $@
