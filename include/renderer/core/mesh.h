#pragma once

#include <vector>

#include <renderer/core/face.h>
#include <renderer/core/vertex.h>

class Mesh{
public:
    std::vector<Face> faces;
    Vertex center;  // Rotation pivot

    Mesh() = default;
    Mesh(const std::vector<Face>& constructFaces, const Vertex& meshCenter)
        : faces(constructFaces), center(meshCenter) {}

    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);

    void Move(float dx, float dy, float dz);
    void Scale(float scale_factor);

private:
    void RotateVertexX(Vertex& v, float cosA, float sinA);
    void RotateVertexY(Vertex& v, float cosA, float sinA);
    void RotateVertexZ(Vertex& v, float cosA, float sinA);
};
