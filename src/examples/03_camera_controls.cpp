#include <renderer/all.h>
#include <renderer/loaders/obj_loader.h>
#include <renderer/camera.h>

int main() {
    Renderer renderer(1000, 700, "03 - Camera Controls");
    Obj_loader loader;

    Mesh model = loader.load_obj(""); // Change to your absolute path to some .obj file
    for (auto& f : model.faces) f.color = Color(255, 150, 100); // Set model color

    Camera camera(0, 100, -800, 0, 0, 0, 1200.0f); // Camera starting position
    SDL_SetWindowRelativeMouseMode(renderer.GetWindow(), true); // Lock cursor to the window for better camera control

    while (renderer.IsRunning()) {
        renderer.PollEvents();
        renderer.Clear(0x00000000);

        camera.CameraMovement();

        for (auto& face : model.faces) {
            Face cf(
                camera.WorldToCamera(face.v1),
                camera.WorldToCamera(face.v2),
                camera.WorldToCamera(face.v3),
                face.color
            );
            renderer.DrawFace3D(cf, camera.focal_length);
        }

        renderer.Present();
    }
}
