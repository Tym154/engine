#pragma once

#include <cmath>

#include <renderer/face.h>

Face::Face(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Color& faceColor){
        v1 = vertex1;
        v2 = vertex2;
        v3 = vertex3;
        color = faceColor;
        normal_vector = ComputeNormal();
}

Vertex Face::ComputeNormal(){
    // Compute vectors
    Vertex u = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
    Vertex v = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};

    // Cross product
    Vertex normal_vector = {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };

    // Normalize
    float length = std::sqrt(normal_vector.x * normal_vector.x +
                             normal_vector.y * normal_vector.y +
                             normal_vector.z * normal_vector.z);
    if (length != 0){
        normal_vector.x /= length;
        normal_vector.y /= length;
        normal_vector.z /= length;
    }

    return normal_vector;
}