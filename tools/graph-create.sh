#! /bin/bash

echo "> Creating graph : .dot to .png AND .dot to .svg"
#launched from bash in saturncc dir
cd tools 
mkdir -p graph-last-program
dot -Tpng ../after_syntax.dot -o graph-last-program/after_syntax.png
dot -Tsvg ../after_syntax.dot -o graph-last-program/after_syntax.svg
dot -Tpng ../after_passe_1.dot -o graph-last-program/after_passe_1.png
dot -Tsvg ../after_passe_1.dot -o graph-last-program/after_passe_1.svg
