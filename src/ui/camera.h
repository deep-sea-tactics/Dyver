

#include <SDL3/SDL.h>
#include <string>
#include <vector>

class CameraFeed {
public:
    CameraFeed(SDL_Renderer* renderer, int cameraIndex = 0);
    ~CameraFeed();

    bool openCamera();
    void updateTexture();
    void render(int x, int y, int width, int height);
    bool isRunning() const { return camera != nullptr; }

private:
    SDL_Renderer* renderer = nullptr;
    SDL_Camera* camera = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Surface* currentFrame = nullptr;
    int cameraIndex;
};


