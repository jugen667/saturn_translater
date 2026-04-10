
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
else ifeq ($(DEBUG_YACC),1)
	YACC_FLAGS=-t 
endif


CFLAGS=-O0 -g -std=c99 -DYY_NO_LEAKS
INCLUDE=-I$(INC_DIR) 

all: $(EXE)

$(EXE) :  y.tab.o lex.yy.o common.o tree_analysis.o instruction_set.o gen_code.o
	@echo "| Linking files : $^"
	@echo "| Creating binary $@"
	@gcc $(CFLAGS) $(INCLUDE) y.tab.o lex.yy.o common.o tree_analysis.o instruction_set.o gen_code.o -o $@
	@echo "| Cleaning .o files"
	@rm -f *.o
	@echo "| \033[1mFinished building $(EXE)\033[0m"


y.tab.c: $(GRA_DIR)/grammar.y Makefile
	@echo "| Creating parser $@"
	@yacc $(YACC_FLAGS)-d $(GRA_DIR)/grammar.y
	@mv y.tab.c $(SRC_DIR)
	@mv y.tab.h $(INC_DIR)

lex.yy.c: $(GRA_DIR)/lexico.l Makefile
	@echo "| Creating lexical analyser $@"
	@lex -o $(SRC_DIR)/lex.yy.c $(LEX_FLAGS) $(GRA_DIR)/lexico.l

lex.yy.o: lex.yy.c
	@echo "| Compiling $<"
	@gcc -D_GNU_SOURCE $(YACC_FLAGS) $(CFLAGS) $(INCLUDE) -o $@ -c $(SRC_DIR)/$<

y.tab.o: y.tab.c
	@echo "| Compiling $<"
	@gcc $(YACC_FLAGS) $(CFLAGS) $(INCLUDE) -o $@ -c $(SRC_DIR)/$<

common.o: $(SRC_DIR)/common.c $(INC_DIR)/common.h $(INC_DIR)/defs.h Makefile
	@echo "| Compiling $<"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

tree_analysis.o: $(SRC_DIR)/tree_analysis.c $(INC_DIR)/tree_analysis.h $(INC_DIR)/defs.h $(INC_DIR)/common.h Makefile
	@echo "| Compiling $<"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

instruction_set.o: $(SRC_DIR)/instruction_set.c $(INC_DIR)/defs.h $(INC_DIR)/common.h $(INC_DIR)/instruction_set.h Makefile
	@echo "| Compiling $<"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<


gen_code.o: $(SRC_DIR)/gen_code.c $(INC_DIR)/gen_code.h $(INC_DIR)/defs.h $(INC_DIR)/common.h Makefile
	@echo "| Compiling $<"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

# keeping the binary for delivery
clean-delivery:  
	@echo "| Cleaning all files except binary"
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
	@echo "| \033[1mCleaned all files\033[0m"

