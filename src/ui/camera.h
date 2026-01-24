#ifndef camera_h
#define camera_h

#include "SDL3/SDL_render.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_camera.h>

class camera {
public:
    camera(SDL_Renderer* renderer = nullptr, int width = 640, int height = 480, int camindex = 0);
    ~camera();

    // Methods
    bool init();
    void update();
    void render(SDL_FRect* dstRect = nullptr);
    void close();

    bool isInitialized() const { return m_initialized; }

private:
    SDL_Renderer* m_renderer = nullptr;
    SDL_Camera* m_camera = nullptr;
    SDL_Texture* m_texture = nullptr;
    int m_cameraIndex;
    bool m_initialized = false;
    int width;
    int height;

    // Helper functions
    bool openCameraDevice();
    void acquireAndProcessFrame();

};


#endif