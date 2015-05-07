BIN=../bin/rlspyka
CC=gcc
SRC=../src/rlspyk_analysis.c rlspyka.c
INC=-I../inc
HDR=$(wildcard ../inc/*.h)
CFLAGS=-ggdb3

$(BIN) : $(SRC) $(HDR)
	$(CC) $(filter %.c, $^) -o $(BIN) $(INC) $(CFLAGS)
