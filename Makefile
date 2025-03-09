CC = g++
CFLAGS = -Wall -std=c++17 -lssl -lcrypto

OBJ = lexer.o parser.o vcs.o utils.o galaxy.o

all: galaxy

lexer.cpp: lexer.l
	win_flex -o lexer.cpp lexer.l

galaxy: $(OBJ)
	$(CC) -o galaxy $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o galaxy lexer.cpp