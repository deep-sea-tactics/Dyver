#include "app.h"

void app_t::run()
{
	std::shared_ptr<window_helper_t> window = std::make_shared<window_helper_t>("Dyver");

	SDL_Event event;
	while (m_running) // See app_t declaration
	{
		while (SDL_PollEvent(&event)) // Keep polling events for as long as they are coming
		{
			if (event.type == SDL_EVENT_QUIT)
			{
					kill();
			}
		}
		// Render widgets
	}
}
