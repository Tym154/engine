#include <cmath>

#include <renderer/core/face.h>

Face::Face(const Vertex& v_1, const Vertex& v_2, const Vertex& v_3, const Color& face_color){
        this->v1 = v_1;
        this->v2 = v_2;
        this->v3 = v_3;
        color = face_color;
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