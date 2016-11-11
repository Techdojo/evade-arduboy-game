#ifndef PLAYER_H
#define PLAYER_H

#include "Arduboy.h"
#include "globals.h"

struct Player {
  int x;
  int y;
  int width;
  int height;
  int frame;
  int health;

  void set() {
    x = 2;
    y = 32;
    frame = 2;
    width = 16;
    height = 16;
    health = 100;
  }

  void reset() {
    x = 2;
    y = 32;
    frame = 2;
    health = 100;
  }
};

#endif
