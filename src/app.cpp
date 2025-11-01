#include "app.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"

void app_t::run()
{
    SDL_Init(SDL_INIT_VIDEO);
    window_helper_t window = window_helper_t("Dyver"); // TODO: Configure version with DSS

    SDL_Event event;
    while (running) // See app_t declaration
    {
        while (SDL_PollEvent(&event)) // Keep polling events for as long as they are coming
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                kill();
            }
        }
    }
}