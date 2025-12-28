#include "camera.h"
#include <iostream>
#include <SDL3/SDL_camera.h>


CameraFeed::CameraFeed(SDL_Renderer* rend, int camIndex) 
    : renderer(rend), cameraIndex(camIndex) {}

CameraFeed::~CameraFeed() {
    if (currentFrame) {
        SDL_ReleaseCameraFrame(camera, currentFrame);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (camera) {
        SDL_CloseCamera(camera);
    }
}

bool CameraFeed::openCamera() {

    // Enumerate camera devices
    SDL_CameraID* deviceNames= SDL_GetCameras(NULL);
    if (!deviceNames || !deviceNames[cameraIndex]) {
        std::cerr << "Error: Cannot find camera device at index " << cameraIndex << std::endl;
        return false;
    }

    // Open the camera device, requesting RGBA8888 format for compatibility
    // The API will attempt conversion if the native format differs

    SDL_Camera *camera = SDL_OpenCamera(deviceNames[cameraIndex], NULL);
    SDL_free(deviceNames);

    if (!camera) {
        std::cerr << "Error: Could not open camera device: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Camera opened successfully." << std::endl;
    return true;
}

void CameraFeed::updateTexture() {
    // Acquire a new frame
    Uint64 timestamp;
    SDL_Surface* nextFrame = SDL_AcquireCameraFrame(camera, &timestamp);
    
    if (nextFrame) {
        if (!texture) {
            // Create texture when the first frame is available
            texture = SDL_CreateTexture(renderer, nextFrame->format, SDL_TEXTUREACCESS_STATIC, nextFrame->w, nextFrame->h);
            if (!texture) {
                std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
                SDL_ReleaseCameraFrame(camera, nextFrame);
                return;
            }
        }
        
        // Update the texture with new pixel data
        SDL_UpdateTexture(texture, NULL, nextFrame->pixels, nextFrame->pitch);
        
        // Release the previous frame and store the current one
        if (currentFrame) {
            SDL_ReleaseCameraFrame(camera, currentFrame);
        }
        currentFrame = nextFrame;
    }
}

void CameraFeed::render(int x, int y, int width, int height) {
    if (texture) {
        SDL_FRect dstRect = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) };
        SDL_RenderTexture(renderer, texture, NULL, &dstRect);
    }
}
