# C to Saturn Assembly translater
Simplified C to Saturn (HP-48x) assembly translater 

## Main features

Produces a binary file that convert a C program into a Saturn assembly program.
This also can produce a tree of the program.

## About C
We are using a sub-set of C. 
This subset is mainly limited by the instruction set of the Saturn CPU.

More about the subset under [grammar/rules.md](https://github.com/jugen667/saturn_translater/blob/master/grammar/rules.md)

## Useful ressources
- Instruction set and documentation: [Introduction to Saturn Asembly Language](https://www.keesvandersanden.nl/calculators/downloads/Saturn_tutorial.pdf)
- General information about Saturn Architecture : [HP Saturn](https://en.wikipedia.org/wiki/HP_Saturn)
- The HP 48 that inspired that project : [HP 48 series](https://en.wikipedia.org/wiki/HP_48_series)
- HP Calc archive : [hpcalc.org](https://www.hpcalc.org/)

## Utils
Clone the repo : ```git clone https://github.com/jugen667/saturn_translater```

Fast test file with tree as png and svg :

```make clean && make all && bin/saturncc -a temp/test.c && tools/graph-create.sh```


# KNOWN BUGS 

- Mixing 'OR' and 'AND' in conditionnal makes the instruction creation messy : to fix ?

---------------


# Road Map

## ~~Add float support~~

## ~~Ensure tree is correct~~

## ~~1st parsing : ensure we are doing operations correctly (type checks etc)~~

## ~~Instruction Set implementation~~ 

### ~~Check what we need it in our arch~~

- ~~registers setups~~
- ~~instuctions list~~

## 2nd parsing : translate nodes to instructions with the instructions set
- ~~int operations~~
- ~~bool operation~~ 
- ~~if~~
- ~~while / do...while~~
- ~~for~~

## Optimization to do :
- revamp conditionnal operations construction
- ~~consecutive prio nodes~~
- NOT operation in AND
- AND and OR in the same condition  




## TO DO IN THE FUTURE ##

- Add support for more C function (incremental operator ?)
- Pointers maybe ?
- ~~Address management (func loop etc)~~
- String support
- add ARM instruction set compatibility and compilation option (not sure)



