#ifndef OPPONENT_H
#define OPPONENT_H
#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 6, 6) {
    x_ = x;
    y_ = y;
  }
  virtual void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& object) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {
    x_ = x;
    y_ = y;
  }
  virtual void Move(const graphics::Image& object) override;
  virtual void Draw(graphics::Image& screen) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int counter_ = 0;
};

#endif
