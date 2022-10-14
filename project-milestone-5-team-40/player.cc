#include "player.h"

#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"

void PlayerProjectile::Move(const graphics::Image& img) {
  y_ = y_ - 7;
  SetY(y_);
  is_active_ = !(IsOutOfBounds(img));
}

void PlayerProjectile::Draw(graphics::Image& screen) {
  screen.DrawRectangle(x_ + 1, y_, 2, 2, kBlue);
  screen.DrawRectangle(x_, y_ + 3, 2, 2, kBlue);
  screen.DrawRectangle(x_ + 3, y_ + 3, 2, 2, kBlue);
}

void Player::Draw(graphics::Image& screen) {
  // Draws Arms to player
  screen.DrawLine(0 + x_, 15 + y_, 9 + x_, 15 + y_, 137, 207, 240, 10);
  screen.DrawLine(40 + x_, 15 + y_, 49 + x_, 15 + y_, 137, 207, 240, 10);
  // Draws Legs to player
  screen.DrawLine(20 + x_, 30 + y_, 20 + x_, 45 + y_, 137, 207, 240, 5);
  screen.DrawLine(30 + x_, 30 + y_, 30 + x_, 45 + y_, 137, 207, 240, 5);
  // Draws Shoes to player
  screen.DrawLine(20 + x_, 45 + y_, 20 + x_, 49 + y_, 0, 0, 0, 5);
  screen.DrawLine(30 + x_, 45 + y_, 30 + x_, 49 + y_, 0, 0, 0, 5);
  // Draw Torso to player
  screen.DrawRectangle(10 + x_, 0 + y_, 30, 35, 137, 207, 240);
  // Draw Eyes to player
  screen.DrawCircle(20 + x_, 8 + y_, 4, 255, 255, 255);
  screen.DrawCircle(30 + x_, 8 + y_, 4, 255, 255, 255);
  screen.DrawCircle(20 + x_, 8 + y_, 2, 0, 0, 0);
  screen.DrawCircle(30 + x_, 8 + y_, 2, 0, 0, 0);
}

void Player::Move(const graphics::Image& img) {}
