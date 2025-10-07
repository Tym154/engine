#include <renderer/all.h>
#include <renderer/loaders/obj_loader.h>
#include <renderer/camera.h>

int main() {
    Renderer renderer(1000, 700, "04 - Backface Culling");
    Obj_loader loader;

    Mesh mesh = loader.load_obj(""); // Change to your absolute path to some .obj file
    for (auto& f : mesh.faces) f.color = Color(180, 220, 180);

    Camera camera(0, 0, -800, 0, 0, 0, 1200.0f);

    SDL_SetWindowRelativeMouseMode(renderer.GetWindow(), true); // Lock cursor to the window for better camera control

    while (renderer.IsRunning()) {
        renderer.PollEvents();
        renderer.Clear(0x00000000);
        camera.CameraMovement();

        for (auto& f : mesh.faces) {
            if (renderer.IsBackface(f, camera)) continue;
            Face cf(
                camera.WorldToCamera(f.v1),
                camera.WorldToCamera(f.v2),
                camera.WorldToCamera(f.v3),
                f.color
            );
            renderer.DrawFace3D(cf, camera.focal_length);
        }

        renderer.Present();
    }
}
