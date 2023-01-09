CC = g++

PART1 = Game
PART2 = Server
PART3 = Client

all: $(PART1) $(PART2) $(PART3)

clean:
	rm -f *.o *~ $(PART1) $(PART2) $(PART3)

.PHONY: all clean

$(PART1): srcAnt/antDeclaration.cpp srcAnt/ant.cpp srcAnt/ant.h srcAnt/board.cpp srcAnt/board.h srcAnt/integerCheck.h srcAnt/integerCheck.cpp srcAnt/outputManager.cpp srcAnt/outputManager.h
	$(CC) $^ -o $@
	$(CC) -lpthread $^ -o $@

$(PART2): Sockets/server.h Sockets/server.cpp Sockets/dataDef.h Sockets/dataDef.cpp Sockets/main.cpp Sockets/klient.h Sockets/klient.cpp
	$(CC) $^ -o $@
	$(CC) -lpthread $^ -o $@

$(PART3): Sockets/klient.h Sockets/klient.cpp Sockets/dataDef.h Sockets/dataDef.cpp Sockets/main.cpp Sockets/server.h Sockets/server.cpp
	$(CC) $^ -o $@
	$(CC) -lpthread $^ -o $@

%.o: %.c
	$(CC) $< -c