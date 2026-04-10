#! /bin/bash

echo "> Creating graph : .dot to .png AND .dot to .svg"
#launched from bash in saturncc dir
cd tools 
mkdir -p graph-last-program
dot -Tpng ../after_syntax_check.dot -o graph-last-program/after_syntax_check.png
dot -Tsvg ../after_syntax_check.dot -o graph-last-program/after_syntax_check.svg
dot -Tpng ../after_tree_analysis.dot -o graph-last-program/after_tree_analysis.png
dot -Tsvg ../after_tree_analysis.dot -o graph-last-program/after_tree_analysis.svg
