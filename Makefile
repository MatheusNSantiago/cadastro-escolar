CFLAGS = -Wall
CC = gcc

OBJDIR = objects
BINDIR = bin

SRC := $(shell find . -name '*.c')
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

all: binfolder objfolder bin/cadastro-escolar
	@./bin/cadastro-escolar

bin/cadastro-escolar: $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

binfolder:
	@mkdir -p $(BINDIR)

objfolder:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%main.o: main.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c %.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -Rf bin objects