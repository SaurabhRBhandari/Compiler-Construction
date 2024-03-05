# Purpose: Makefile for the project

# Lexical Analyzer
lexer.o: lexer.c lexerDef.h
		@gcc -c lexer.c

# Syntax Analyzer
parser.o: parser.c lexerDef.h parserDef.h
		@gcc -c parser.c 

# Driver Code
driver.o: driver.c lexerDef.h parserDef.h utils.h lexer.h parser.h
		@gcc -c driver.c

# Utilities
utils.o: utils.c utils.h
		@gcc -c utils.c

# Trie data structure
trie.o: data_structures/trie.c data_structures/trie.h
		@gcc -c data_structures/trie.c

# Vector data structure
vector.o: data_structures/vector.c data_structures/vector.h
		@gcc -c data_structures/vector.c

# Compile all the .o files
compile: driver.o lexer.o parser.o utils.o trie.o vector.o
		@gcc -o exec driver.o lexer.o parser.o utils.o trie.o vector.o
		@rm *.o

# Run the executable
run: exec
		@./exec 

# Clean the .o files and the executable
clean:
		@rm -f *.o exec
		@rm -f data_structures/*.o 

# Compile, run and clean
all: compile run clean
