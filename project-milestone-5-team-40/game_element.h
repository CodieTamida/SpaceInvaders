
#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H
#include <iostream>
#include <vector>

#include "cpputils/graphics/image.h"

class GameElement {
 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;

 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  void SetIsActive(bool is_active) { is_active_ = is_active; }
  bool GetIsActive() const { return is_active_; }
  bool IsOutOfBounds(const graphics::Image& object);
  bool IntersectsWith(const GameElement* object);
  virtual void Move(const graphics::Image& img) = 0;
  virtual void Draw(graphics::Image& screen) = 0;
  virtual void SetX(int x) { x_ = x; }
  virtual void SetY(int y) { y_ = y; }
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
};
#endif
