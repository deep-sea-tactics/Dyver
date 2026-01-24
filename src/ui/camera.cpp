#include "ui/camera.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_camera.h>
#include <SDL3/SDL_render.h>


camera::camera(SDL_Renderer* renderer, int width, int height, int camindex)
    : m_renderer(renderer), m_cameraIndex(camindex), width(width), height(height)
{
    if (renderer == nullptr) {
            SDL_Log("Camera constructor: Renderer is null!\n");
    }
}

camera::~camera()
{
    close();
}

bool camera::init()
{
    if (!openCameraDevice()) {
        SDL_Log("Failed to open camera device.\n");
        return false;
    }

    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!m_texture) {
        SDL_Log("Failed to create texture: %s\n", SDL_GetError());
        return false;
    }

    m_initialized = true;
    return true;
}

void camera::update()
{
    if (!m_initialized) {
        SDL_Log("Camera not initialized. Call init() first.\n");
        return;
    }

    acquireAndProcessFrame();
}

void camera::render(SDL_FRect* dstRect)
{
    if (!m_initialized) {
        SDL_Log("Camera not initialized. Call init() first.\n");
        return;
    }

    

    SDL_RenderTexture(m_renderer, m_texture, NULL, dstRect);
}

void camera::close()
{
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    if (m_camera) {
        SDL_CloseCamera(m_camera);
        m_camera = nullptr;
    }

    m_initialized = false;
}

bool camera::openCameraDevice()
{
    m_camera = SDL_OpenCamera(m_cameraIndex, NULL);
    if (!m_camera) {
        SDL_Log("Failed to open camera index %d: %s\n", m_cameraIndex, SDL_GetError());
        return false;
    }
    return true;
}

void camera::acquireAndProcessFrame()
{
    Uint64 timestampNS = 0;
    SDL_Surface* frame = SDL_AcquireCameraFrame(m_camera, &timestampNS);
    if (!frame) {
        SDL_Log("Failed to capture frame: %s\n", SDL_GetError());
        return;
    }

    // Update texture with the captured frame data
    SDL_UpdateTexture(m_texture, nullptr, frame->pixels, frame->pitch);

    SDL_ReleaseCameraFrame(m_camera, frame);
}

