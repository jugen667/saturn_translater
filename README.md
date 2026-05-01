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
- Instruction set and documentation: [Introduction to Saturn Assembly Language](https://www.keesvandersanden.nl/calculators/downloads/Saturn_tutorial.pdf)
- General information about Saturn Architecture : [HP Saturn](https://en.wikipedia.org/wiki/HP_Saturn)
- The HP 48 that inspired that project : [HP 48 series](https://en.wikipedia.org/wiki/HP_48_series)
- HP Calc archive : [hpcalc.org](https://www.hpcalc.org/)

## Utils

Clone the repo : ```git clone https://github.com/jugen667/saturn_translater```

Compile from source : ```make clean && make all && bin/saturncc your-file.c -o output-file.s```

To display help, type ```bin/saturncc -h```


# KNOWN BUGS 

**1. Conditionnal boolean operations : mixing operations (LT and PLUS for example) is broken.**

Temporary fix : add parenthesis to ensure the operations to be compared is executed 

Example : Replace ```if(!(i<2+1))``` by ```if(!(i<(2+1))``` 


**2. Mixing AND and OR in a single condition check is not working.**

Temprary fix : Avoid mixing OR and AND for your operations

Example : make multiple ```if``` / use a temporary variable and do your checks on it


**3. Multiple operations in a single instructions is broken.**

Temprary fix : create multiple instruction, 1 for each operation

Example : Replace ```sum = 2+(end*4);``` by ```sum = end*4; sum += 2;```


---------------


## IMPROVEMENTS TO DO ##

- Add support for more C function (goto, Pointers, Functions etc)
- add ARM instruction set compatibility and compilation option (not sure)



