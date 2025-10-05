#include <cmath>
#include <vector>
#include <iostream>

#include <renderer/all.h>
#include <renderer/loaders/obj_loader.h>

const int WIDTH = 1600;
const int HEIGHT = 1000;
const float FOCAL_LENGTH = 1200.0f;

int main() {
    Renderer renderer(WIDTH, HEIGHT, "Software 3D Renderer");

    Obj_loader loader;
    Mesh objMesh = loader.load_obj(""); // Load OBJ file
    printf("Loaded %zu faces from OBJ file.\n", objMesh.faces.size());

    if (objMesh.faces.empty()) {
        std::cerr << "Failed to load OBJ or file is empty!" << std::endl;
        return 1;
    }

    // Main render loop
    while (renderer.IsRunning()) {
        renderer.PollEvents();
        renderer.Clear(0x00000000); // Black background

        // Rotate the mesh slowly around the Y axis
        objMesh.RotateY(-0.002f);


        // Draw all faces
        for (const Face& face : objMesh.faces) {
                renderer.DrawFace3D(face, FOCAL_LENGTH);
        }

        renderer.Present();
    }

    return 0;
}
