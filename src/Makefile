CC = g++
CFLAGS = -Wall -std=c++17 -lssl -lcrypto

OBJ = parser.o vcs.o branch.o config.o utils.o galaxy.o

all: galaxy

galaxy: $(OBJ)
	$(CC) -o galaxy $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o galaxy