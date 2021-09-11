
CC = gcc
CC_OPTS = -Wall

BIN = bin
OUT = setbaud
IN = src/setbaud.c

all: $(BIN) $(BIN)/$(OUT)

$(BIN):
	mkdir $(BIN)

$(BIN)/$(OUT): $(IN)
	$(CC) $(CC_OPTS) -o $@ $^

.PHONY: man clean

man:
	COLUMNS=128 man --nh --nj -M doc $(OUT) > doc/$(OUT).man.txt

clean:
	rm -f $(BIN)/*
