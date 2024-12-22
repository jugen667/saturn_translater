
EXE:=bin/saturncc
SRC_DIR:=src
INC_DIR:=include
GRA_DIR:=grammar

DEBUG_LEX=0 
DEBUG_YACC=0

YACC_FLAGS=
LEX_FLAGS=

ifeq ($(DEBUG_LEX),1)
	LEX_FLAGS=-DLEX_DEBUG=1
endif
ifeq ($(DEBUG_YACC),1)
	YACC_FLAGS=-DYYDEBUG=1
endif


CFLAGS=-O0 -g -std=c99 -DYY_NO_LEAKS -Wimplicit-function-declaration
INCLUDE=-I$(INC_DIR) 

all: $(EXE)

# $(EXE) : y.tab.o lex.yy.o arch.o common.o passe_1.o passe_2.o
#	@gcc $(CFLAGS) $(INCLUDE) -L$(UTILS) y.tab.o lex.yy.o arch.o common.o passe_1.o passe_2.o -o $@ -lminiccutils
$(EXE) :  y.tab.o lex.yy.o arch.o common.o passe_1.o instruction_set.o 
	@echo "| Linking / Creating binary $@"
	@gcc $(CFLAGS) $(INCLUDE) y.tab.o lex.yy.o arch.o common.o passe_1.o instruction_set.o -o $@
	@echo "| Cleaning .o files"
	@rm -f *.o
	@echo "| Finished compilation"


y.tab.c: $(GRA_DIR)/grammar.y Makefile
	@echo "| yacc -d grammar.y"
	@yacc -d $(GRA_DIR)/grammar.y
	@mv y.tab.c $(SRC_DIR)
	@mv y.tab.h $(INC_DIR)

lex.yy.c: $(GRA_DIR)/lexico.l Makefile
	@echo "| lex $(LEX_FLAGS) -d lexico.l"
	@lex -o $(SRC_DIR)/lex.yy.c $(LEX_FLAGS) $(GRA_DIR)/lexico.l

lex.yy.o: lex.yy.c
	@echo "| Compiling $@"
	@gcc -D_GNU_SOURCE $(YACC_FLAGS) $(CFLAGS) $(INCLUDE) -o $@ -c $(SRC_DIR)/$<

y.tab.o: y.tab.c
	@echo "| Compiling $@"
	@gcc $(YACC_FLAGS) $(CFLAGS) $(INCLUDE) -o $@ -c $(SRC_DIR)/$<

arch.o: $(SRC_DIR)/arch.c $(INC_DIR)/arch.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

common.o: $(SRC_DIR)/common.c $(INC_DIR)/common.h $(INC_DIR)/arch.h $(INC_DIR)/defs.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

passe_1.o: $(SRC_DIR)/passe_1.c $(INC_DIR)/passe_1.h $(INC_DIR)/defs.h $(INC_DIR)/common.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

instruction_set.o: $(SRC_DIR)/instruction_set.c $(INC_DIR)/defs.h $(INC_DIR)/common.h $(INC_DIR)/instruction_set.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

# passe_2.o: $(SRC_DIR)/passe_2.c $(INC_DIR)/passe_2.h $(INC_DIR)/arch.h $(INC_DIR)/defs.h $(INC_DIR)/common.h Makefile
# 	@echo "| Compiling $@"
# 	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

# keeping the binary
clean-soft:  
	@echo "| Cleaning all files"
	@echo "| Cleaning .o files"
	@rm -f *.o
	@echo "| Cleaning lex and grammar files"
	@rm -f $(SRC_DIR)/y.tab.c $(INC_DIR)/y.tab.h $(SRC_DIR)/lex.yy.c 
	@echo "| Cleaning built files"
	@rm -f *.s *.dot
	@rm -rf tools/graph-last-program
	@echo "| Cleaning test files"
	@rm -f  tests/log.txt tests/buffer.txt tests/*.s tests/*.dot *.txt

# remove all 
clean: 
	@echo "| Cleaning all files"
	@echo "| Cleaning binary"
	@rm -f $(EXE)
	@echo "| Cleaning .o files"
	@rm -f *.o
	@echo "| Cleaning lex and grammar files"
	@rm -f $(SRC_DIR)/y.tab.c $(INC_DIR)/y.tab.h $(SRC_DIR)/lex.yy.c 
	@echo "| Cleaning built files"
	@rm -f *.s *.dot
	@rm -rf tools/graph-last-program
	@echo "| Cleaning test files"
	@rm -f  tests/log.txt tests/buffer.txt tests/*.s tests/*.dot *.txt

