#pragma once

#include <renderer/vertex.h>
#include <renderer/color.h>

class Face{
public:
    Vertex v1, v2, v3;
    Color color;
    Vertex normal_vector;

    Face() = default;
    Face(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Color& faceColor);

    Vertex ComputeNormal();
};