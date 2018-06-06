CC = g++
override CFLAGS += -Wall -Wextra -lm -g
GLFLAGS = -lGL -lGLU -lglut
TARGET = ships

$(TARGET): display.o ship.o player.o
	$(CC) -o $@ $^ $(CFLAGS) $(GLFLAGS) 

player.o: player.cpp player.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

ship.o: ship.cpp ship.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

display.o: display.cpp display.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(TARGET)
	
