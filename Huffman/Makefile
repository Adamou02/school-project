CC = gcc
CFLAGS = -Wall

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
EXE = Projet

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@

$(OBJ): %.o : %.c 
	$(CC) $(CFLASG) -c $< -o $@

.PHONY: clean

clean: 
	rm -f $(OBJ)