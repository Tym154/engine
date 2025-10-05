#pragma once

#include <vector>

#include <renderer/face.h>
#include <renderer/vertex.h>

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

private:
    void RotateVertexX(Vertex& v, float cosA, float sinA);
    void RotateVertexY(Vertex& v, float cosA, float sinA);
    void RotateVertexZ(Vertex& v, float cosA, float sinA);
};
