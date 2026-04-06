#!/bin/bash

make clean 
make all 
# bin/saturncc -a tests/test-while.c -o out-while.s
# bin/saturncc -a tests/test-if.c -o out-if.s
# bin/saturncc -a tests/test-for.c -o out-for.s
# bin/saturncc -a tests/test-dowhile.c -o out-dowhile.s
tools/graph-create.sh