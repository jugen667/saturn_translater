# C to Saturn Assembly translater
Simplified C to Saturn (HP-48x) assembly translater 

## Main features

Produces a binary file that convert a C program into a Saturn assembly program.
This also can produce a tree of the program.

## About C
We are using a sub-set of C. 
This subset is limited by the instruction set of the Saturn CPU.

More about the subset under [grammar/rules.md](https://github.com/jugen667/saturn_translater/blob/master/grammar/rules.md)

## Utils
Clone the repo : ```git clone https://github.com/jugen667/saturn_translater```

Fast test file with tree as png and svg :

```make clean && make all && bin/saturncc temp/test.c && tools/graph-create.sh```

# Road Map

## ~~Add float support~~

## ~~Ensure tree is correct~~

## 1st parsing : ensure we are doing operations correctly (type checks etc)

### Check if we need it in our arch

#### TO TEST ####

#### TO DO ####

- Pointers
- Address management (func loop etc)
- String support
- Add support for more C function (incremental operator ?)


## Instruction Set implementation 

- registers setups
- instuctions list


## 2nd parsing : translate nodes to instructions with the instructions set



# KNOWN BUGS 
