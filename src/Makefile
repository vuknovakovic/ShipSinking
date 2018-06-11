CC = g++
override CFLAGS += -Wall -Wextra -lm -g
GLFLAGS = -lGL -lGLU -lglut
TARGET = ships

$(TARGET): main.o phase1.o ship.o player.o game.o phase2.o
	$(CC) -o $@ $^ $(CFLAGS) $(GLFLAGS) 

player.o: player.cpp ../includes/player.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

ship.o: ship.cpp ../includes/ship.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

phase1.o: phase1.cpp ../includes/phase1.hpp ship.cpp game.cpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

phase2.o: phase2.cpp ../includes/phase2.hpp ship.cpp game.cpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

game.o: game.cpp ../includes/game.hpp phase1.cpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

main.o: main.cpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(TARGET)
	
