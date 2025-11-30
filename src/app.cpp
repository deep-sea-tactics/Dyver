

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "app.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "ui/Window.h"
#include "ui/UI.h"
#include "ui/camera.h"

#include <memory>

void app_t::run()
{
    SDL_Init(SDL_INIT_VIDEO);
    //window_helper_t window = window_helper_t("Dyver"); // TODO: Configure version with DSS
    UI UIManager;
    Window GameWindow;

    bool running = true; //

    SDL_Event event;
    while (running) // See app_t declaration
    {
        while (SDL_PollEvent(&event)) // Keep polling events for as long as they are coming
        {   UIManager.HandleEvent(event); //
            if (event.type == SDL_EVENT_QUIT) 
            {
                //kill();
                running = false; //
            }
        }

      

        GameWindow.Render(); // Render the window (clear it with a color)
        UIManager.Render(GameWindow.GetSurface()); // Render the UI elements onto the window surface
        GameWindow.Update(); //
        // Render widgets
    }
    //SDL_Quit(); //
}

/*
void app_t::run() 
{
  SDL_Init(SDL_INIT_VIDEO);
  Window GameWindow;
  UI UIManager;

  bool IsRunning = true;
  SDL_Event Event;
  while (IsRunning) {
    while (SDL_PollEvent(&Event)) {
      UIManager.HandleEvent(Event);
      if (Event.type == SDL_EVENT_QUIT) {
        IsRunning = false;
      }
    }

    GameWindow.Render();
    UIManager.Render(GameWindow.GetSurface());
    GameWindow.Update();
  }

  SDL_Quit();
}
*/
