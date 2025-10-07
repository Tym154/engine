#include <renderer/all.h>
#include <renderer/loaders/obj_loader.h>
#include <renderer/camera.h>

int main() {
    Renderer renderer(800, 600, "02 - Transformations");
    Obj_loader loader;
    Mesh cube = loader.load_obj(""); // Change to your absolute path to some .obj file
    for (auto& f : cube.faces) f.color = Color(150, 220, 255);

    Camera cam(0, 0, -800, 0, 0, 0, 1200.0f);

    while (renderer.IsRunning()) {
        renderer.PollEvents();
        renderer.Clear(0x00000000);

        cube.RotateY(0.02f);
        cube.RotateX(0.01f);

        for (auto& f : cube.faces) {
            Face cf(
                cam.WorldToCamera(f.v1),
                cam.WorldToCamera(f.v2),
                cam.WorldToCamera(f.v3),
                f.color
            );
            renderer.DrawFace3D(cf, cam.focal_length);
        }

        renderer.Present();
    }
}
