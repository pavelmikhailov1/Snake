#include "snake.h"

std::random_device rd;
std::mt19937 gen(rd());

int g_score{0};
int g_lives{3};
int g_speed{100000};

Snake::Snake() : SnakeNode{10, 10} {
  tail.push_back(SnakeNode{9, 10});
  tail.push_back(SnakeNode{8, 10});
}

Food::Food(std::vector<SnakeNode>& tail) { foodRebase(tail); }

Game::Game() : Snake(), Food(this->tail){}

void Snake::snakeRebase() {
  this->snakeX = 10;
  this->snakeY = 10;
  tail.resize(0);
  tail.push_back(SnakeNode{9, 10});
  tail.push_back(SnakeNode{8, 10});
}

void Food::foodRebase(std::vector<SnakeNode>& tail) {
  foodX = gen() % (X_MAX - 2) + 1;
  foodY = gen() % (Y_MAX - 2) + 1;
  if (tail.size() != 0) {
    for (size_t i{0}; i < tail.size() - 1; i++) {
      if ((foodX == tail.at(i).snakeX && foodY == tail.at(i).snakeY)) {
        foodRebase(tail);
        break;
      }
    }
  }
}

void Game::createField() {
  control();
  logic();
  print();
}

void Game::print() {
  clear();
  printw("lives: %d \t\t SNAKE\t\t     score: %d\n", g_lives, g_score);
  for (int i{0}; i < Y_MAX; i++) {
    for (int j{0}; j < X_MAX; j++) {
      if (i == 0 && j != 0) {
        if (j != X_MAX - 1) 
          printw("%c", '_');
        else {
          printw("%c\n", ' ');
        }
        continue;
      }
      if (j == 0 || j == X_MAX - 1) {
        if (i != 0 && i != Y_MAX - 1) {
          printw("%c", '|');
          if (j == X_MAX - 1) printw("\n");
          continue;
        }
      }
      if (i == Y_MAX - 1) {
        printw("%c", '-');
        continue;
      }
      if (i == this->foodY && j == this->foodX) {
        printw("%c", '*');
        continue;
      }
      if (i == this->snakeY && j == this->snakeX) {
        printw("%c", 'Q');
        continue;
      }
      bool flag{false};
      for (size_t k{0}; k < this->tail.size(); k++) {
        if (i == this->tail.at(k).snakeY && j == this->tail.at(k).snakeX) {
          printw("%c", 'o');
          flag = true;
        }
      }
      if (!flag) printw("%c", ' ');
    }
  }
}

void Game::logic() {
  int headXBuff{this->snakeX};
  int headyBuff{this->snakeY};

  if (direction == kUp)
    this->snakeY -= 1;
  else if (direction == kDown)
    this->snakeY += 1;
  else if (direction == kLeft)
    this->snakeX -= 1;
  else if (direction == kRight)
    this->snakeX += 1;

  snakeX %= X_MAX - 2;
  snakeY %= Y_MAX - 2;
  if (snakeX == 0) snakeX = X_MAX - 2;
  if (snakeY == 0) snakeY = Y_MAX - 2;

  if (this->snakeY == this->foodY && this->snakeX == this->foodX) {
    g_score += 10;
    if (g_speed > SPEED_MAX) g_speed -= 500;
    this->tail.push_back(SnakeNode{});
    this->foodRebase(this->tail);
  }

  for (auto i{this->tail.size() - 1}; i > 0; i--) {
    if (this->snakeX == this->tail.at(i).snakeX &&
        this->snakeY == this->tail.at(i).snakeY) {
      g_lives--;
      snakeRebase();
      break;
    }
    this->tail.at(i).snakeX = tail.at(i - 1).snakeX;
    this->tail.at(i).snakeY = tail.at(i - 1).snakeY;
  }
  this->tail.at(0).snakeX = headXBuff;
  this->tail.at(0).snakeY = headyBuff;
}

void Game::control() {
  int ch = getch();
  switch (ch) {
    case KEY_UP:
      SET_DIRECTION(kDown, kUp);
      break;
    case KEY_DOWN:
      SET_DIRECTION(kUp, kDown);
      break;
    case KEY_LEFT:
      SET_DIRECTION(kRight, kLeft);
      break;
    case KEY_RIGHT:
      SET_DIRECTION(kLeft, kRight);
      break;
    case 'w':
      g_speed -= 3000;
      break;
    case 's':
      g_speed += 3000;
      break;
    case 'q':
      clear();
      endwin();
      std::cout << "You score: " << g_score << std::endl;
      exit(0);
  }
  flushinp();
}

int main() {
  setlocale(0, "");
  initscr();
  cbreak();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);
  noecho();

  Game game;

  while (g_lives) {
    game.createField();
    usleep(g_speed);
  }

  clear();
  endwin();
  std::cout << "Game over! You score: " << g_score << std::endl;
  return 0;
}
