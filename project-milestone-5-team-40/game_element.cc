#include "game_element.h"

#include "cpputils/graphics/image.h"

void GameElement::Draw(graphics::Image& screen) {
  screen.DrawRectangle(x_, y_, 5, 5, 0, 0, 0);
}

bool GameElement::IntersectsWith(const GameElement* object) {
  return !(x_ > object->GetX() + object->GetWidth() ||
           object->GetX() > GetX() + GetWidth() ||
           y_ > object->GetY() + object->GetHeight() ||
           object->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image& object) {
  if (x_ <= 0 || y_ <= 0 || y_ >= object.GetHeight() ||
      x_ >= object.GetWidth()) {
    return true;
  } else {
    return false;
  }
}
