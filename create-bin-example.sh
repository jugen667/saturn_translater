#!/bin/bash

make clean && make all && bin/saturncc -d -a tests/test-if.c && tools/graph-create.sh
read -p "Press any key to continue"