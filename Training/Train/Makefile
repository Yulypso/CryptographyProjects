CC = gcc
CC_FLAGS = -Wall
SRCDIR   = src
EXEC = TRAINING

all: compile

run: 
	@./$(EXEC)

compile:
	@$(CC) $(CC_FLAGS) $(SRCDIR)/*.c -o $(EXEC) 

clean:
	@rm -rf $(EXEC)