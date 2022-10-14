#include "game.h"

#include <iostream>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  int x = event.GetX();
  int y = event.GetY();

  if (event.GetMouseAction() == graphics::MouseAction::kMoved) {
    if (!(y + player_.GetWidth() + player_.GetHeight() > screen_.GetHeight() ||
          x + player_.GetWidth() + player_.GetHeight() > screen_.GetWidth() ||
          y < 0 || x < 0)) {
      player_.SetX(x - 25);
      player_.SetY(y - 25);
    } else {
      player_.SetX(player_.GetX());
      player_.SetY(player_.GetY());
    }
  } else if (event.GetMouseAction() == graphics::MouseAction::kDragged) {
    if (!(y + player_.GetWidth() + player_.GetHeight() > screen_.GetHeight() ||
          x + player_.GetWidth() + player_.GetHeight() > screen_.GetWidth() ||
          y < 0 || x < 0)) {
      player_.SetX(x - 25);
      player_.SetY(y - 25);
      auto ptr = std::unique_ptr<PlayerProjectile>{
          new PlayerProjectile(player_.GetX() + 22, player_.GetY())};
      player_projectile_.push_back(std::move(ptr));
    } else {
      player_.SetX(player_.GetX());
      player_.SetY(player_.GetY());
    }
  } else if (event.GetMouseAction() == graphics::MouseAction::kPressed) {
    auto ptr = std::unique_ptr<PlayerProjectile>{
        new PlayerProjectile(player_.GetX() + 22, player_.GetY())};
    player_projectile_.push_back(std::move(ptr));
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive()) {
      auto projectile = opponent_[i]->LaunchProjectile();
      if (projectile == nullptr) {
      } else {
        opponent_projectile_.push_back(std::move(projectile));
      }
    }
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive()) {
      opponent_[i]->Move(screen_);
    }
  }
  for (int i = 0; i < opponent_projectile_.size(); i++) {
    if (opponent_projectile_[i]->GetIsActive()) {
      opponent_projectile_[i]->Move(screen_);
    }
  }
  for (int i = 0; i < player_projectile_.size(); i++) {
    if (player_projectile_[i]->GetIsActive()) {
      player_projectile_[i]->Move(screen_);
    }
  }
}
void Game::FilterIntersections() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->IntersectsWith(&player_)) {
      player_.SetIsActive(false);
      opponent_[i]->SetIsActive(false);
      SetStatus(true);
    }
  }
  for (int i = 0; i < opponent_projectile_.size(); i++) {
    if (opponent_projectile_[i]->IntersectsWith(&player_)) {
      opponent_projectile_[i]->SetIsActive(false);
      player_.SetIsActive(false);
      SetStatus(true);
    }
  }
  for (int i = 0; i < player_projectile_.size(); i++) {
    for (int j = 0; j < opponent_.size(); j++) {
      if (player_projectile_[i]->IntersectsWith(opponent_[j].get())) {
        player_projectile_[i]->SetIsActive(false);
        opponent_[j]->SetIsActive(false);
        if (player_.GetIsActive()) {
          SetScore(score_ + 1);
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  if (opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen_.Flush();
}

void Game::CreateOpponents() {
  auto opp1 = std::unique_ptr<Opponent>{new Opponent(200, 30)};
  auto opp2 = std::unique_ptr<Opponent>{new Opponent(375, 10)};

  opponent_.push_back(std::move(opp1));
  opponent_.push_back(std::move(opp2));
}

void Game::Init() {
  Player me(375, 500);
  player_ = me;
  CreateOpponents();
  screen_.AddMouseEventListener(*this);
  screen_.AddAnimationEventListener(*this);
}

void Game::RemoveInactive() {
  for (int i = opponent_.size() - 1; i >= 0; i--) {
    if (opponent_[i]->GetIsActive() == false) {
      opponent_.erase(opponent_.begin() + i);
    }
    for (int i = opponent_projectile_.size() - 1; i >= 0; i--) {
      if (opponent_projectile_[i]->GetIsActive() == false) {
        opponent_projectile_.erase(opponent_projectile_.begin() + i);
      }
    }
    for (int i = player_projectile_.size() - 1; i >= 0; i--) {
      if (player_projectile_[i]->GetIsActive() == false) {
        player_projectile_.erase(player_projectile_.begin() + i);
      }
    }
  }
}
void Game::UpdateScreen() {
  std::string scoreString = std::to_string(score_);
  screen_.DrawRectangle(0, 0, screen_.GetWidth(), screen_.GetHeight(), 255, 255,
                        255);
  screen_.DrawText(10, 5, scoreString, 25, 86, 29, 94);
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive()) {
      opponent_[i]->Draw(screen_);
    }
  }
  for (int i = 0; i < opponent_projectile_.size(); i++) {
    if (opponent_projectile_[i]->GetIsActive()) {
      opponent_projectile_[i]->Draw(screen_);
    }
  }
  for (int i = 0; i < player_projectile_.size(); i++) {
    if (player_projectile_[i]->GetIsActive()) {
      player_projectile_[i]->Draw(screen_);
    }
  }
  if (player_.GetIsActive()) {
    player_.Draw(screen_);
  }
}

void Game::Start() { screen_.ShowUntilClosed(); }
