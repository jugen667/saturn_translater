#! /bin/bash

echo "Creating graph : .dot to .png AND .dot to .svg"
#launched from bash in saturncc dir
cd tools 
mkdir graph-last-program
dot -Tpng ../apres_syntaxe.dot -o graph-last-program/apres_syntaxe.png
dot -Tsvg ../apres_syntaxe.dot -o graph-last-program/apres_syntaxe.svg
dot -Tpng ../apres_passe_1.dot -o graph-last-program/apres_passe_1.png
dot -Tsvg ../apres_passe_1.dot -o graph-last-program/apres_passe_1.svg

