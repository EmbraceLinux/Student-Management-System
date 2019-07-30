CC=gcc
STD=-std=gnu99
LIB=-lm
INC=-I./include
OBJ=admin.o dao.o list.o main.o sims.o tools.o user.o
BIN=sims.bin
FLAG=-Wall -Werror -DDEBUG

all:$(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BIN)
%.o:%.c
	$(CC) $(STD) $(INC) -c $< -o $@

clean:
	rm $(OBJ) $(BIN)

