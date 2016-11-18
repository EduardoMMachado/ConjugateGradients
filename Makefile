# Implementado por Eduardo Machado e Bruna Maciel
# 2016

CC=gcc
LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj
FLAGS = -Wall -Wextra -lm -g -DLIKWID_PERFMON -O3 -march=native -mtune=intel -mavx

main:	linearSystemCreator cgMethod
	$(CC) $(SRC)/main.c $(OBJ)/linearSystemCreator.o $(OBJ)/cgMethod.o $(FLAGS) -I$(INCLUDE) -L$(LIB) -o cgSolver

linearSystemCreator:
	$(CC) -c $(SRC)/linearSystemCreator.c $(FLAGS) -I$(INCLUDE) -o $(OBJ)/linearSystemCreator.o
	ar -cr $(LIB)/linearSystemCreator.a $(OBJ)/linearSystemCreator.o

cgMethod:
	$(CC) -c $(SRC)/cgMethod.c $(FLAGS) -I$(INCLUDE) -o $(OBJ)/cgMethod.o
	ar -cr $(LIB)/cgMethod.a $(OBJ)/cgMethod.o

clean:
	rm cgSolver core $(SRC)/*~ $(OBJ)/*o $(LIB)/*a
