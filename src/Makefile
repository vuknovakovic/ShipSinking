CC = g++
CFLAGS = -Wall -Wextra -lm -g
GLFLAGS = -lGL -lGLU -lglut
TARGET = ships

$(TARGET): display.o ship.o
	$(CC) -o $@ $^ $(CFLAGS) $(GLFLAGS) 

ship.o: ship.cpp ship.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

display.o: display.cpp display.hpp
	$(CC) $(CFLAGS) $(GLFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(TARGET)
	
