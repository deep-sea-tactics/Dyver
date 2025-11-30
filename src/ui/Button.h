
#pragma once
#include <SDL3/SDL.h>
#include "Rectangle.h"

class UI;

class Button : public Rectangle {
 public:
 Button(UI& UIManager, const SDL_Rect& Rect)
  : Rectangle{Rect},
    UIManager{UIManager}
  {
    SetColor({255, 165, 0, 255});
  }

 void OnLeftClick() override;

private:
  UI& UIManager;
};


