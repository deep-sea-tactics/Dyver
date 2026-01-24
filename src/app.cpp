#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"

//#include "app.h"
#include "SDL3/SDL_video.h"
#include "ui/camera.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>


int main()
//void app_t::run()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA)!= 0)
	{
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_RESIZABLE ); // TODO: Configure version with DSS
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	camera cam(renderer, 640, 480, 0);
	if (!cam.init())
	{
		SDL_Log("Failed to initialize camera.\n");
		SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
		return 1;
	}

	bool quit = false;
	SDL_Event event;
	while (!quit) // See app_t declaration original: while (m_running)
	{
		while (SDL_PollEvent(&event)) // Keep polling events for as long as they are coming
		{
			if (event.type == SDL_EVENT_QUIT)
			{
					//kill();
					quit = true;
			}
		}
		// Render widgets
			cam.update();
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        	SDL_RenderClear(renderer);
			cam.render();
       		SDL_RenderPresent(renderer);


	}

	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
