#pragma once

#include <renderer/vertex.h>

class Camera{
public:
    Vertex position;
    float pitch; // rotation around X axis
    float yaw;   // rotation around Y axis
    float roll;  // rotation around Z axis

    float fov; // field of view in degrees
    float focal_length; // focal length based on FOV and aspect ratio
    float aspect_ratio;

    Camera(float x, float y, float z, float focal_lenght, float fov_degrees, float aspect_ratio);

    void Move(float dx, float dy, float dz);
    void Rotate(float dpitch, float dyaw, float droll);
    void SetPosition(float x, float y, float z);
    void SetRotation(float pitch, float yaw, float roll);

    Vertex WorldToCamera(const Vertex& v) const;
    Vertex Project(const Vertex& v, int screenWidth, int screenHeight) const;
};