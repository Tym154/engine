#include <iostream>
#include <algorithm>
#include <cstring>

#include <renderer/renderer.h>

Renderer::Renderer(int width, int height, const char* title) : width(width), height(height), running(true), window(nullptr), sdlRenderer(nullptr), texture(nullptr), pixels(nullptr){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_FULLSCREEN);
    if (!window){ 
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    sdlRenderer = SDL_CreateRenderer(window, nullptr);
    texture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    pixels = new uint32_t[width * height];
}

Renderer::~Renderer(){
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Clear(uint32_t color){
    std::fill(pixels, pixels + width * height, color);
}

void Renderer::Present(){
    SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(uint32_t));
    SDL_RenderClear(sdlRenderer);
    SDL_RenderTexture(sdlRenderer, texture, nullptr, nullptr);
    SDL_RenderPresent(sdlRenderer);
}

void Renderer::DrawPixel(int x, int y, uint32_t color){
    if (x < 0 || y < 0 || x >= width || y >= height) return;
    pixels[y * width + x] = color;
}

// Bresenham's line algorithm
void Renderer::DrawLine(int x0, int y0, int x1, int y1, uint32_t color){
    int dx = std::abs(x1 - x0);
    int dy = -std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;

    while (true){
        DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy){ err += dy; x0 += sx; }
        if (e2 <= dx){ err += dx; y0 += sy; }
    }
}

void Renderer::DrawFace3D(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color){
    DrawLine(x0, y0, x1, y1, color);
    DrawLine(x1, y1, x2, y2, color);
    DrawLine(x2, y2, x0, y0, color);
}

bool Renderer::IsRunning(){
    return running;
}

void Renderer::PollEvents(){
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_EVENT_QUIT){
            running = false;
        }
    }
}

Vertex Renderer::ProjectTo2D(const Vertex& point, float focalLength, int screenWidth, int screenHeight){
    float x = (focalLength * point.x) / point.z;
    float y = (focalLength * point.y) / point.z;

    x += screenWidth / 2.0f;
    y = screenHeight / 2.0f - y;

    return {x, y, point.z};
}

void Renderer::DrawFace3D(const Face& tri, float focalLength){
    Vertex p0 = ProjectTo2D(tri.v1, focalLength, width, height);
    Vertex p1 = ProjectTo2D(tri.v2, focalLength, width, height);
    Vertex p2 = ProjectTo2D(tri.v3, focalLength, width, height);

    DrawFace3D((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, tri.color.ColorToUint32());
}


void Renderer::DrawMesh3D(const Mesh& mesh, float focalLength){
    for (const Face& face : mesh.faces){
        DrawFace3D(face, focalLength);
    }
}