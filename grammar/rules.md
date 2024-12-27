# C subset ruleset
This file describes the rules of the C subset allowed
> [!NOTE]
> This file is up to modification depending on project advancements, rules may evolve

## Subset of C
This <u>subset of C</u> used fot simple program and as a proof-of-concept for a Saturn compiler. It has the same syntax.
It allows global variables, a *main()* function, loops, branches and *printf()*.
However, it is a very primitive language and thus its functionnalities are limited, by the Saturn HP CPU limitations.

## Removed functionnalities
- **No functions** are allowed except the *main()*

- **No pointers**, and **casting** variable is **not supported** implying the language is strongly typed

- Currently impossible to add composite data types (such as **struct**, **typedef**, **union**)

- No support of **user inputs**

## About data types
### Supported
- **int** : 16-bit integer [-32767; +32767]
- **bool** : classic boolean type : *true (1)* or *false (0)* 
- **float** : supported 
- **void** : void type used for *main()* function
- Strings allowed in *printf()* function

### Not Supported 
- **char** and **string <u>as variable</u>**
- **short** 
- **unsigned** types

Variables propreties such as **volatile**, **register**, **packed**, **inline**, **static** and **extern** are **not implemented**.

## About loops and branches

### Supported 
These loops and branches have the same syntax as C
- *for*
- *while*
- *do{ ... }while*
- *if* 
	> *else* should be supported but is currently not implemented

### Not Supported 
- **switch / case**, 
- **break** and **continue**
- **label** and thus **goto**

## About operators
### Supported 
- **Arithmetic operators** ( +, -, /, *, %)
- **Bitwise operators**  (&, |, ~, ^)
- **Bit Shift operators** (>>, <<, >>>)
- **Logical operators** (&&, ||, !)
- **Conditionnal operators** (==, !=, <, >, <=, >=)
- **Direct Assignement** (=)
- **Comma** as a separator for definition and assignement 
> Ex : int a = 1 **,** int b = 2;
- **Comment** (// and /\*\*/)

### Not Supported 
- **Incremental operators** (++, --)
- **Other type of assignement** (*=, +=, -=, ...)
- **All pointer operators**
- **Function calls** except *print()*
- **Comma**
- **Ternary conditional**
- ***sizeof*** and ***alignof***
- **Casting**



