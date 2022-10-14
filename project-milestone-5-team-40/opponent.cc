#include "opponent.h"

#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"

void OpponentProjectile::Draw(graphics::Image& screen) {
  screen.DrawRectangle(x_, y_, 2, 2, 255, 165, 0);
  screen.DrawRectangle(x_ + 3, y_, 2, 2, 255, 165, 0);
  screen.DrawRectangle(x_, y_ + 3, 2, 2, 255, 165, 0);
}

void OpponentProjectile::Move(const graphics::Image& img) {
  y_ = y_ + 7;
  SetY(y_);
  is_active_ = !(IsOutOfBounds(img));
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  auto ptr = nullptr;
  if (counter_ < 20) {
    auto ptr = nullptr;
  } else {
    auto ptr = std::unique_ptr<OpponentProjectile>{
        new OpponentProjectile(x_ + 35, y_ + 35)};
    counter_ = 0;
    return ptr;
  }
  counter_ += 1;
  return ptr;
}

void Opponent::Draw(graphics::Image& screen) {
  // Arms to the enemy robot
  screen.DrawLine(0 + x_, 15 + y_, 9 + x_, 15 + y_, 238, 75, 43, 10);
  screen.DrawLine(40 + x_, 15 + y_, 49 + x_, 15 + y_, 238, 75, 43, 10);
  // Legs to the enemy robot
  screen.DrawLine(20 + x_, 30 + y_, 20 + x_, 45 + y_, 238, 75, 43, 5);
  screen.DrawLine(30 + x_, 30 + y_, 30 + x_, 45 + y_, 238, 75, 43, 5);
  // Shoes to the enemy robot
  screen.DrawLine(20 + x_, 45 + y_, 20 + x_, 49 + y_, 0, 0, 0, 5);
  screen.DrawLine(30 + x_, 45 + y_, 30 + x_, 49 + y_, 0, 0, 0, 5);
  // Body to the enemy robot
  screen.DrawRectangle(10 + x_, 0 + y_, 30, 35, 238, 75, 43);
  // Eyes to the enemy robot
  screen.DrawCircle(20 + x_, 8 + y_, 4, 255, 255, 255);
  screen.DrawCircle(30 + x_, 8 + y_, 4, 255, 255, 255);
  screen.DrawCircle(20 + x_, 8 + y_, 2, 0, 0, 0);
  screen.DrawCircle(30 + x_, 8 + y_, 2, 0, 0, 0);
}

void Opponent::Move(const graphics::Image& img) {
  x_ = x_ + 3;
  y_ = y_ + 1;
  SetY(y_);
  SetX(x_);
  is_active_ = !(IsOutOfBounds(img));
}
