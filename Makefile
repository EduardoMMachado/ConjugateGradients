# Implementado por Eduardo Machado e Bruna Maciel
# 2016

CC=gcc
LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj
FLAGS = -Wall -lm

main:	linearSystemCreator cgMethod
	$(CC) $(SRC)/main.c $(OBJ)/linearSystemCreator.o $(OBJ)/cgMethod.o $(FLAGS) -I$(INCLUDE) -L$(LIB) -o sgSolver

linearSystemCreator:
	$(CC) -c $(SRC)/linearSystemCreator.c $(FLAGS) -I$(INCLUDE) -o $(OBJ)/linearSystemCreator.o
	ar -cru $(LIB)/linearSystemCreator.a $(OBJ)/linearSystemCreator.o

cgMethod:
	$(CC) -c $(SRC)/cgMethod.c $(FLAGS) -I$(INCLUDE) -o $(OBJ)/cgMethod.o
	ar -cru $(LIB)/cgMethod.a $(OBJ)/cgMethod

clean:
	rm linearSystemCreator core $(SRC)/*~ $(OBJ)/*o $(LIB)/*a
	rm cgMethod core $(SRC)/*~ $(OBJ)/*o $(LIB)/*a
