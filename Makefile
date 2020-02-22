CC=g++
CPPFLAGS= -lSDL2 -lSDL2_image -pthread -Wl,-rpath=.
all: snake
snake: key_listener.o field.o
	$(CC) game.cpp key_listener.o snake.o field.o -o snake $(CPPFLAGS)
key_listener.o: key_listener.cpp key_listener.hpp snake.o
	$(CC) -c key_listener.cpp -o key_listener.o $(CPPFLAGS)
field.o: field.cpp field.hpp
	$(CC) -c field.cpp -o field.o $(CPPFLAGS)
snake.o: snake.cpp snake.hpp
	$(CC) -c snake.cpp -o snake.o $(CPPFLAGS)
start:
	./snake
clean:
	rm -f *.o
