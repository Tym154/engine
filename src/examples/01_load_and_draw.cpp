#include <renderer/all.h>
#include <renderer/loaders/obj_loader.h>
#include <renderer/camera.h>

int main() {
    Renderer renderer(800, 600, "01 - Load & Draw");
    Obj_loader loader;

    Mesh mesh = loader.load_obj(""); // Change to your absolute path to some .obj file
    for (auto& f : mesh.faces) f.color = Color(200, 200, 200);

    Camera cam(0, 200, -1000, 0, 0, 0, 1200.0f); // Adjust camera position

    while (renderer.IsRunning()) {
        renderer.PollEvents();
        renderer.Clear(0x00000000);

        for (auto& face : mesh.faces) {
            Face cf(
                cam.WorldToCamera(face.v1),
                cam.WorldToCamera(face.v2),
                cam.WorldToCamera(face.v3),
                face.color
            );
            renderer.DrawFaceEdges3D(cf, cam.focal_length);
        }

        renderer.Present();
    }
}
