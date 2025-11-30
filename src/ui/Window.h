#pragma once
#include <SDL3/SDL.h>

class Window {
public:

  int initialHeight = 1080;
  int initialWidth = 1920;
  Window() {
    SDLWindow = SDL_CreateWindow(
      "Dyver",
      initialWidth, initialHeight, 0
    );
  }

  void Render() {
    const auto* Fmt = SDL_GetPixelFormatDetails(
      GetSurface()->format
    );
    SDL_FillSurfaceRect(
      GetSurface(),
      nullptr,
      SDL_MapRGB(Fmt, nullptr, 50, 50, 50)
    );
  }

  void Update() {
    SDL_UpdateWindowSurface(SDLWindow);
  }

  SDL_Surface* GetSurface() const {
    return SDL_GetWindowSurface(SDLWindow);
  }

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  ~Window() {
    if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(SDLWindow);
    }
  }

private:
  SDL_Window* SDLWindow{nullptr};
};