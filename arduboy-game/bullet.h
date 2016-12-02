#ifndef BULLET_H
#define BULLET_H

/*
 *  File: bullet.h
 *  Purpose: Deals with player and enemy bullet logic for Evade game.
 *  Author: Modus Create
 */

#include "globals.h"
#include "bitmaps.h"

#define A_BULLET_DAMAGE 75 // First button, Fireball
#define B_BULLET_DAMAGE 40 // Second button, small laser

struct Bullet {
  public:
    float x,
          speedX;
    byte y,
         damage,
         // Visibility (0), Direction (1), Laser Beam (2)
         options;
    unsigned long inGameFireFrame;
    
    void set(byte _x, byte _y, bool firedByPlayer, byte _damage, float _speedX, bool isLaserBeam) {
      x = _x;
      y = _y;
      damage = _damage;
      speedX = _speedX;

      options &= ~(1 << 1);
      options &= ~(1 << 2);
      
      options |= 1 << 0;
      options |= firedByPlayer << 1;
      options |= isLaserBeam << 2;

      inGameFireFrame = inGameFrame;
      draw();
    }

    void update() {
      if (isVisible()) {
        move();
        draw();
      }
    }

    void move() {
      x += isMovingRight() ? speedX : -speedX;
      if (x > 128) {
          hide();
      }
      if (x <= -30) {
          hide();
      }
    }

    void draw() {
        if (isMovingRight()) {
          const bool isBulletA = (damage == A_BULLET_DAMAGE);
          playTone(isBulletA ? 600 - (x + 2) : 900 - (x * 2 + 3), 10);
          drawBitmap(x, y, (isBulletA ? playerBulletA : playerBulletB), 0);
        } else if (!isLaserBeam()) {
          drawBitmap(x, y, enemyBullet, 0);
        } else {
          arduboy.fillRect(x, y, min((inGameFrame, inGameFireFrame), 30), 2, 1);
        }   
    }

    bool isHittingObject(byte objectX, byte objectY, byte objectWidth, byte objectHeight) {
      if ((isVisible()) &&
        ((isLaserBeam() && (x >= (objectX - 30))) || (!isLaserBeam() && (x >= objectX))) &&
        (x <= (objectX + objectWidth)) &&
        (y >= objectY) &&
        (y <= (objectY + objectHeight))) {
        return true;
      } else {
        return false;
      }
    }

    bool isVisible() {
      return (options & (1 << 0));
    }

    bool isMovingRight() {
      return (options & (1 << 1));
    }

    bool isLaserBeam() {
      return (options & (1 << 2));
    }

    void hide() {
      if (isVisible()) {
        options ^= 1 << 0;
      }
    }
};

#endif
