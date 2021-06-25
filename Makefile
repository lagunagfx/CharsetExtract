CC=gcc
CFLAGS=-g -Wall
OBJS=obj/%.o
BIN=bin/charset-extract

SUBMISSION=myproject.zip

all: $(BIN)

main: $(OBJS
	$(CC) $(CFLAGS) $(OBJS) -o main

%.o : %.c
	$(CC) $(FLAGS) -c %< -o %@ 

clean:
	$(RM) -r $(OBJ)/*.o $(OBJ)/*.dSYM

submit:

	$(RM) $(SUBMISSION)
	zip -9 $(SUBMISSION) $(BIN)
