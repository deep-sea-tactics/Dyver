#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"

#include "app.h"
#include "SDL3/SDL_video.h"
//#include "ui/camera.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>


static SDL_Texture *texture = NULL;
static SDL_Renderer *renderer = NULL;
SDL_CameraID *devices = NULL;
int devcount = 0;

//int main()
void app_t::run()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA))
	{
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	SDL_Window* window = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_RESIZABLE ); // TODO: Configure version with DSS

	devices = SDL_GetCameras(&devcount);
    if (devices == NULL) {
        SDL_Log("Couldn't enumerate camera devices: %s", SDL_GetError());
        return;
    } else if (devcount == 0) {
        SDL_Log("Couldn't find any camera devices! Please connect a camera and try again.");
        return;
    }

	SDL_Camera*	camera = SDL_OpenCamera(devices[0], NULL);  // just take the first thing we see in any format it wants.
    SDL_free(devices);
    if (camera == NULL) {
        SDL_Log("Couldn't open camera: %s", SDL_GetError());
        return;
	}



	//bool quit = false;
	SDL_Event event;
	while (m_running) // See app_t declaration original: while (m_running)
	{
		while (SDL_PollEvent(&event)) // Keep polling events for as long as they are coming
		{
			if (event.type == SDL_EVENT_QUIT)
			{
					kill();
					//quit = true;
			}
			
			else if (event.type == SDL_EVENT_CAMERA_DEVICE_APPROVED)
			{
				SDL_Log("Camera device approved event received.\n");
			}

			else if (event.type == SDL_EVENT_CAMERA_DEVICE_DENIED)
			{
				SDL_Log("Camera device rejected event received.\n");
			
				return;
			}
		}
		// Render widgets

		Uint64 timestampNS = 0;
    	SDL_Surface *frame = SDL_AcquireCameraFrame(camera, &timestampNS);


		 if (frame != NULL) {
        /* Some platforms (like Emscripten) don't know _what_ the camera offers
           until the user gives permission, so we build the texture and resize
           the window when we get a first frame from the camera. */
		   if (!texture) {
            SDL_SetWindowSize(window, frame->w, frame->h);  /* Resize the window to match */
            SDL_SetRenderLogicalPresentation(renderer, frame->w, frame->h, SDL_LOGICAL_PRESENTATION_LETTERBOX);
            texture = SDL_CreateTexture(renderer, frame->format, SDL_TEXTUREACCESS_STREAMING, frame->w, frame->h);
        	}

			if (texture) {
            	SDL_UpdateTexture(texture, NULL, frame->pixels, frame->pitch);
        	}

			SDL_ReleaseCameraFrame(camera, frame);

		}

		SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x99, SDL_ALPHA_OPAQUE);
    	SDL_RenderClear(renderer);
    	if (texture) {  /* draw the latest camera frame, if available. */
        	SDL_RenderTexture(renderer, texture, NULL, NULL);
    	}
    	SDL_RenderPresent(renderer);


	}

	SDL_CloseCamera(camera);
    SDL_DestroyTexture(texture);

	return;
}
