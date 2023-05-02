#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <ncurses.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#define SET_DIRECTION(A, B) \
  if (direction != A) direction = B;
#define X_MAX 55
#define Y_MAX 16
#define SPEED_MAX 50000

enum Direction { kLeft = 0, kRight, kUp, kDown };

struct SnakeNode {
  int snakeX{};
  int snakeY{};
};

class Snake : public SnakeNode {
 public:
  std::vector<SnakeNode> tail{0};

  Snake();

  void snakeRebase();
};

class Food {
 public:
  int foodX{};
  int foodY{};

  Food(std::vector<SnakeNode>& tail);

  void foodRebase(std::vector<SnakeNode>& tail);
};

class Game : public Snake, Food {
 public:
  bool gameOver{false};
  int direction{kRight};
  Game();

  void createField();
  void print();
  void logic();
  void control();
};

#endif  //_SNAKE_H_