#include <cmath>

#include <renderer/camera.h>

static inline float toRadians(float deg) { return deg * 3.14159265f / 180.0f; }

Camera::Camera(float x, float y, float z, float focal_lenght, float fov_degrees, float aspect_ratio = 16 / 9) 
    : position{x, y, z}, pitch(0), yaw(0), roll(0), fov(fov_degrees), aspect_ratio(aspect_ratio) {

    // Calculate focal length based on FOV and aspect ratio
    float fov_radians = fov * (3.14159265f / 180.0f);
    this->focal_length = focal_lenght;
}

void Camera::Move(float dx, float dy, float dz){
        position.x += dx;
        position.y += dy;
        position.z += dz;
}

void Camera::Rotate(float dpitch, float dyaw, float droll){
        pitch += dpitch;
        yaw += dyaw;
        roll += droll;
}

void Camera::SetPosition(float x, float y, float z){ position = {x, y, z}; }

void Camera::SetRotation(float pitch, float yaw, float roll){
        this->pitch = pitch;
        this->yaw = yaw;
        this->roll = roll;
}


Vertex Camera::WorldToCamera(const Vertex& v) const {
    float x = v.x - position.x;
    float y = v.y - position.y;
    float z = v.z - position.z;

    // Apply yaw (Y-axis rotation)
    float cosY = std::cos(yaw);
    float sinY = std::sin(yaw);
    float xz = x * cosY - z * sinY;
    float zz = x * sinY + z * cosY;

    // Apply pitch (X-axis rotation)
    float cosP = std::cos(pitch);
    float sinP = std::sin(pitch);
    float yz = y * cosP - zz * sinP;
    float zz2 = y * sinP + zz * cosP;

    return Vertex(xz, yz, zz2);
}

// Projects camera-space point → 2D screen coordinates
Vertex Camera::Project(const Vertex& v, int screenWidth, int screenHeight) const {
    if (v.z <= 0.1f) return Vertex(-9999, -9999, v.z); // Behind the camera, skip it

    float x_proj = (v.x / (v.z * std::tan(toRadians(fov / 2.0f)))) * aspect_ratio;
    float y_proj = (v.y / (v.z * std::tan(toRadians(fov / 2.0f))));

    int sx = (int)((x_proj + 1.0f) * 0.5f * screenWidth);
    int sy = (int)((1.0f - y_proj) * 0.5f * screenHeight);

    return Vertex((float)sx, (float)sy, v.z);
}
