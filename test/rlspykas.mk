BIN=../bin/rlspykas
CC=gcc
SRC=../src/rlspyk.c rlspykas.c
INC=-I../inc
HDR=$(wildcard ../inc/*.h)
CFLAGS=-ggdb3

$(BIN) : $(SRC) $(HDR)
	$(CC) $(filter %.c, $^) -o $(BIN) $(INC) $(CFLAGS)
