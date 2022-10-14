.#include <iostream>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game game(800, 600);
  game.Init();
  game.UpdateScreen();
  game.Start();
  return 0;
}
