# saturn_translater
Simplified C to Saturn (HP-48x) assembler

## Main features

Produces a binary file that convert a C program into a Saturn assembly program.
This also can produce a tree of the program.

## About C
We are using a sub-set of C. 

More about the subset under [grammar/rules.md](https://github.com/jugen667/saturn_translater/blob/master/grammar/rules.md)

# Road Map

## ~~Add float support~~

## Ensure tree is correct

## 1st parsing : ensure we are doing operations correctly (type checks etc)

### Check if we need it in our arch
- Global context to check
- Variable Decl to check
- If variable not decl : put it in the env (means add an offset to it)
- Offset management (func loop etc)
- String support ?

## Instruction Set implementation 

- registers setups
- instuctions list
- dump in a file

## 1st parsing : translate nodes to instructions with the instructions set



# KNOWN BUGS 

- affectation between declaration or in global throw syntax error :
```C
int start = 0;
int end = 5;
float a = 191.01450;
start = a + end;		<--- Throw Syntax Error
void main () {
	int i, s = start , e = end ;
	int sum = 0;
	for (i = s; i < e; i = i + 1) {
 		sum = sum + 1;	
 	}
	print("sum :", sum , "\n") ;
}
```
```C
int start = 0;
int end = 5;
float a = 191.01450;

void main () {
	int i, s = start , e = end ;
	start = a + end;    <--- Throw Syntax Error
	int sum = 0;
	for (i = s; i < e; i = i + 1) {
 		sum = sum + 1;	
 	}
	print("sum :", sum , "\n") ;
}
```