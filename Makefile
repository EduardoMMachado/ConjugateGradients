# Implementado por Eduardo Machado
# 2016

CC=gcc
LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj
FLAGS = -Wall -lm

main:	linearSystemCreator
	$(CC) $(SRC)/main.c $(OBJ)/linearSystemCreator.o $(FLAGS) -I$(INCLUDE) -L$(LIB) -o sgSolver

linearSystemCreator:
	$(CC) -c $(SRC)/linearSystemCreator.c $(FLAGS) -I$(INCLUDE) -o $(OBJ)/linearSystemCreator.o
	ar -cru $(LIB)/linearSystemCreator.a $(OBJ)/linearSystemCreator.o

clean:
	rm linearSystemCreator core $(SRC)/*~ $(OBJ)/*o $(LIB)/*a
