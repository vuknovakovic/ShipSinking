CC = g++
override CFLAGS += -Wall -Wextra -lm -g
GLFLAGS = -lGL -lGLU -lglut
TARGET = ships

$(TARGET): main.o phase1.o ship.o player.o game.o
	$(CC) -o $@ $^ $(CFLAGS) $(GLFLAGS) 

player.o: player.cpp player.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

ship.o: ship.cpp ship.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

phase1.o: phase1.cpp phase1.hpp ship.cpp game.cpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

game.o: game.cpp game.hpp phase1.cpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

main.o: main.cpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(TARGET)
	
