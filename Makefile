CC := gcc
CFLAGS := -g -Wall
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# be REALLY CAREFUL with spaces: I.E a space inbetween '$(' and 'wilcard' renders the expression invalid
# closing parenthesis seem to have no effect whatsoever

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
BIN = $(BIN_DIR)/charset-extract

SUBMISSION := myproject.zip

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) -r $(BIN_DIR)/* $(OBJ_DIR)/*

# prints any variable when invoked: 'make print-VARIABLE'
# really useful for debug purposes
print-%: ; @echo $* = $($*)

submit:
	$(info Release name is ${SUBMISSION})
	$(RM) $(SUBMISSION)
	zip -9 $(SUBMISSION) $(BIN)
