#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {
    x_ = x;
    y_ = y;
  }
  virtual void Move(const graphics::Image& object) override;
  virtual void Draw(graphics::Image& screen) override;

 protected:
  graphics::Color kBlue{0, 0, 255};
};

class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {
    x_ = x;
    y_ = y;
  }
  virtual void Draw(graphics::Image& screen) override;
  virtual void Move(const graphics::Image& img) override;
};
#endif
