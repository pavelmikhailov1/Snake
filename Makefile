CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic
SOURSES = snake.cpp

all: snake.cpp snake.h
	@$(CC) $(CFLAGS) $(SOURSES) -o snake -lncurses
	@./snake

kill:
	kill -9 $(ps aux | grep ./snake)

clean:
	@rm -rf snake
