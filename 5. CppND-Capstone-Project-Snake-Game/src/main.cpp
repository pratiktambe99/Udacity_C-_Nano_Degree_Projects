#include <iostream>
#include "controller.h"//Include controller.h
#include "game.h"//Include game.h
#include "renderer.h"//Include renderer.h

int main() {
  constexpr std::size_t kFramesPerSecond{60};//Set fps
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};//Set screen width
  constexpr std::size_t kScreenHeight{640};//Set screen height
  constexpr std::size_t kGridWidth{32};//Set grid width
  constexpr std::size_t kGridHeight{32};//Set grid height

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  //Start game
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}