#include <cmath>

#include <renderer/core/mesh.h>

void Mesh::RotateX(float angle) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    for (Face& face : faces) {
        // Rotate vertices around the mesh center
        for (Vertex* v : {&face.v1, &face.v2, &face.v3}) {
            float y = v->y - center.y;
            float z = v->z - center.z;

            float yNew = y * cosA - z * sinA;
            float zNew = y * sinA + z * cosA;

            v->y = yNew + center.y;
            v->z = zNew + center.z;
        }

        // Rotate normal
        float ny = face.normal_vector.y * cosA - face.normal_vector.z * sinA;
        float nz = face.normal_vector.y * sinA + face.normal_vector.z * cosA;

        face.normal_vector.y = ny;
        face.normal_vector.z = nz;
    }
}

void Mesh::RotateY(float angle) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    for (Face& face : faces) {
        // Rotate vertices around the mesh center
        for (Vertex* v : {&face.v1, &face.v2, &face.v3}) {
            float x = v->x - center.x;
            float z = v->z - center.z;

            float xNew = x * cosA + z * sinA;
            float zNew = -x * sinA + z * cosA;

            v->x = xNew + center.x;
            v->z = zNew + center.z;
        }

        // Rotate normal
        float nx = face.normal_vector.x * cosA + face.normal_vector.z * sinA;
        float nz = -face.normal_vector.x * sinA + face.normal_vector.z * cosA;

        face.normal_vector.x = nx;
        face.normal_vector.z = nz;
    }
}

void Mesh::RotateZ(float angle) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    for (Face& face : faces) {
        // Rotate vertices around the mesh center
        for (Vertex* v : {&face.v1, &face.v2, &face.v3}) {
            float x = v->x - center.x;
            float y = v->y - center.y;

            float xNew = x * cosA - y * sinA;
            float yNew = x * sinA + y * cosA;

            v->x = xNew + center.x;
            v->y = yNew + center.y;
        }

        // Rotate normal
        float nx = face.normal_vector.x * cosA - face.normal_vector.y * sinA;
        float ny = face.normal_vector.x * sinA + face.normal_vector.y * cosA;

        face.normal_vector.x = nx;
        face.normal_vector.y = ny;
    }
}


void Mesh::Move(float dx, float dy, float dz) {
    center.x += dx;
    center.y += dy;
    center.z += dz;

    for (Face& face : faces) {
        for (Vertex* v : {&face.v1, &face.v2, &face.v3}) {
            v->x += dx;
            v->y += dy;
            v->z += dz;
        }
    }
}


void Mesh::Scale(float scale_factor) {
    for (Face& face : faces) {
        for (Vertex* v : {&face.v1, &face.v2, &face.v3}) {
            v->x = center.x + (v->x - center.x) * scale_factor;
            v->y = center.y + (v->y - center.y) * scale_factor;
            v->z = center.z + (v->z - center.z) * scale_factor;
        }
    }
}