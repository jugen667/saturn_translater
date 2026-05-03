#!/bin/bash

make clean 
make all 
bin/saturncc tests/test-while.c -o out-while.s
bin/saturncc tests/test-if.c -o out-if.s
bin/saturncc tests/test-for.c -o out-for.s
bin/saturncc tests/test-dowhile.c -o out-dowhile.s
bin/saturncc tests/test-and.c -o out-and.s
bin/saturncc tests/test-or.c -o out-or.s
# tools/graph-create.sh