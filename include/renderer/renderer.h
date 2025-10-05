#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

#include <renderer/mesh.h>
#include <renderer/face.h>
#include <renderer/vertex.h>
#include <renderer/color.h>


class Renderer{
public:
    Renderer(int width, int height, const char* title);
    ~Renderer();

    void Clear(uint32_t color = 0x00000000);
    void Present();

    void DrawPixel(int x, int y, uint32_t color);
    void DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
    void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

    // 3D Face Drawing
    void DrawFace3D(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
    void DrawFace3D(const Face& face, float focalLength);

    void DrawMesh3D(const Mesh& mesh, float focalLength);

    // Projection
    Vertex ProjectTo2D(const Vertex& point, float focalLength, int screenWidth, int screenHeight);

    bool IsRunning();
    void PollEvents();

    SDL_Window* GetWindow() const { return window; } // Expose window for further customization (Not needed now)

private:
    int width, height;
    bool running;

    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    SDL_Texture* texture;
    uint32_t* pixels;

    SDL_Event event;
};
