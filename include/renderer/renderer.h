#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

#include <renderer/core/mesh.h>
#include <renderer/core/face.h>
#include <renderer/core/vertex.h>
#include <renderer/core/color.h>
#include <renderer/camera.h>


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
    void DrawFace3D(const Face& face, float focal_length);
    void DrawFaceEdges3D(const Face& face, float focal_length);

    void DrawMesh3D(const Mesh& mesh, float focal_length);
    void DrawMeshEdges3D(const Mesh& mesh, float focal_length);

    // Projection
    Vertex ProjectTo2D(const Vertex& point, float focal_length, int screen_width, int screen_height);
    bool IsBackface(const Face& face, const Camera& camera);

    bool IsRunning();
    void PollEvents();

    SDL_Window* GetWindow() const { return window; } // Expose window for further scustomization (Not needed now)

private:
    int width, height;
    bool running;

    SDL_Window* window;
    SDL_Renderer* sdl_renderer;
    SDL_Texture* texture;
    uint32_t* pixels;

    SDL_Event event;
};
