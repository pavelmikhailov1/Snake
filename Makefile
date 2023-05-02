CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic
SOURSES = snake.cpp
LINUX =

UNAME =  $(shell uname -s)
ifeq ($(UNAME), Linux)
		LINUX += sudo apt-get install libncurses5-dev libncursesw5-dev
endif


all: snake.cpp snake.h
	$(LINUX)
	@$(CC) $(CFLAGS) $(SOURSES) -o snake -lncurses
	@./snake

kill:
	kill -9 $(ps aux | grep ./snake)

clean:
	@rm -rf snake
