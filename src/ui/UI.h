#pragma once
#include <SDL3/SDL.h>
#include "Rectangle.h"
#include "Button.h"

class UI {
public:
  void Render(SDL_Surface* Surface) const {
    A.Render(Surface);
    B.Render(Surface);
    C.Render(Surface);
  }

  void HandleEvent(SDL_Event& E) {
    A.HandleEvent(E);
    B.HandleEvent(E);
    C.HandleEvent(E);
  }

  void SetRectangleColors(const SDL_Color& Color) {
    A.SetColor(Color);
    B.SetColor(Color);
  }

private:
  Rectangle A{SDL_Rect{50, 50, 50, 50}};
  Rectangle B{SDL_Rect{200, 50, 50, 50}};
  Button C{*this, SDL_Rect{550, 50, 50, 50}};
};