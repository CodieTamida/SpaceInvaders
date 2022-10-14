#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() { screen_.Initialize(800, 600); }
  Game(int height, int width) { screen_.Initialize(height, width); }
  void Init();
  void UpdateScreen();
  void Start();
  void CreateOpponents();
  void MoveGameElements();
  void FilterIntersections();
  void RemoveInactive();
  void LaunchProjectiles();
  void SetStatus(bool gameStatus) { gameStatus_ = gameStatus; }
  void SetScore(int score) { score_ = score; }
  bool HasLost() { return gameStatus_; }
  int GetScore() { return score_; }
  virtual void OnAnimationStep() override;
  virtual void OnMouseEvent(const graphics::MouseEvent& event) override;
  graphics::Image& GetGameScreen() { return screen_; }
  std::vector<std::unique_ptr<Opponent>>& GetOpponents() { return opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return opponent_projectile_;
  }
  // deleted an s
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() {
    return player_projectile_;
  }
  Player& GetPlayer() { return player_; }

 protected:
  int height_;
  int width_;
  bool gameStatus_ = false;
  int score_ = 0;
  graphics::Image screen_;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponent_projectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> player_projectile_;
  Player player_;
};
#endif
