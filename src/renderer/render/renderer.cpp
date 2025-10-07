#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

#include <renderer/renderer.h>

Renderer::Renderer(int width, int height, const char* title) : width(width), height(height), running(true), window(nullptr), sdl_renderer(nullptr), texture(nullptr), pixels(nullptr){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_FULLSCREEN);
    if (!window){ 
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    sdl_renderer = SDL_CreateRenderer(window, nullptr);
    texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    pixels = new uint32_t[width * height];
}

Renderer::~Renderer(){
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Clear(uint32_t color){
    std::fill(pixels, pixels + width * height, color);
}

void Renderer::Present(){
    SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(uint32_t));
    SDL_RenderClear(sdl_renderer);
    SDL_RenderTexture(sdl_renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(sdl_renderer);
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

void Renderer::DrawFace3D(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Sort vertices by y (ascending)
    if (y0 > y1) { std::swap(y0, y1); std::swap(x0, x1); }
    if (y0 > y2) { std::swap(y0, y2); std::swap(x0, x2); }
    if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }

    // Compute inverse slopes
    float dx01 = (y1 - y0) > 0 ? (float)(x1 - x0) / (y1 - y0) : 0;
    float dx02 = (y2 - y0) > 0 ? (float)(x2 - x0) / (y2 - y0) : 0;
    float dx12 = (y2 - y1) > 0 ? (float)(x2 - x1) / (y2 - y1) : 0;

    float sx = x0;
    float ex = x0;

    // Filling top half
    for (int y = y0; y < y1; y++) {
        if (y >= 0 && y < height) {
            int start_x = (int)std::round(sx);
            int end_x   = (int)std::round(ex);
            if (start_x > end_x) std::swap(start_x, end_x);

            for (int x = start_x; x <= end_x; x++) {
                if (x >= 0 && x < width)
                    pixels[y * width + x] = color;
            }
        }
        sx += dx01;
        ex += dx02;
    }

    // Filling bottom half
    sx = x1;
    for (int y = y1; y <= y2; y++) {
        if (y >= 0 && y < height) {
            int start_x = (int)std::round(sx);
            int end_x   = (int)std::round(ex);
            if (start_x > end_x) std::swap(start_x, end_x);

            for (int x = start_x; x <= end_x; x++) {
                if (x >= 0 && x < width)
                    pixels[y * width + x] = color;
            }
        }
        sx += dx12;
        ex += dx02;
    }
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

Vertex Renderer::ProjectTo2D(const Vertex& point, const float focal_length, const int screen_width, const int screen_height){
    float x = (focal_length * point.x) / point.z;
    float y = (focal_length * point.y) / point.z;

    x += screen_width / 2.0f;
    y = screen_height / 2.0f - y;

    return {x, y, point.z};
}

void Renderer::DrawFace3D(const Face& tri, const float focal_length){
    Vertex p0 = ProjectTo2D(tri.v1, focal_length, width, height);
    Vertex p1 = ProjectTo2D(tri.v2, focal_length, width, height);
    Vertex p2 = ProjectTo2D(tri.v3, focal_length, width, height);

    DrawFace3D((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, tri.color.ColorToUint32());
}


void Renderer::DrawMesh3D(const Mesh& mesh, const float focal_length){
    for (const Face& face : mesh.faces){
        DrawFace3D(face, focal_length);
    }
}

bool Renderer::IsBackface(const Face& face, const Camera& camera) {
    Vertex v1_cam = camera.WorldToCamera(face.v1);
    Vertex v2_cam = camera.WorldToCamera(face.v2);
    Vertex v3_cam = camera.WorldToCamera(face.v3);

    Face cam_face(v1_cam, v2_cam, v3_cam, face.color);
    Vertex normal = cam_face.ComputeNormal();


    return normal.z > 0.0f;
}


void Renderer::DrawFaceEdges3D(const Face& face, const float focal_length) {
    Vertex p0 = ProjectTo2D(face.v1, focal_length, width, height);
    Vertex p1 = ProjectTo2D(face.v2, focal_length, width, height);
    Vertex p2 = ProjectTo2D(face.v3, focal_length, width, height);

    uint32_t edgeColor = 0xFFFFFFFF; // White color for edges
    DrawLine((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, edgeColor);
    DrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, edgeColor);
    DrawLine((int)p2.x, (int)p2.y, (int)p0.x, (int)p0.y, edgeColor);
}

void Renderer::DrawMeshEdges3D(const Mesh& mesh, const float focal_length) {
    for (const Face& face : mesh.faces){
        DrawFaceEdges3D(face, focal_length);
    }
}