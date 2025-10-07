#pragma once

#include <SDL3/SDL.h>

#include <renderer/core/vertex.h>

class Camera{
public:
    Vertex position;
    float pitch; // rotation around X axis
    float yaw;   // rotation around Y axis
    float roll;  // rotation around Z axis

    float focal_length;

    Camera(float x, float y, float z, float init_pitch, float init_yaw, float init_roll, float focal_lenght);

    void Move(float dx, float dy, float dz);
    void Rotate(float dpitch, float dyaw, float droll);
    void SetPosition(float x, float y, float z);
    void SetRotation(float pitch, float yaw, float roll);

    void CameraMovement(float moveSpeed = 0.8, float mouseSensitivity = 0.0005);

    Vertex WorldToCamera(const Vertex& v) const;
    Vertex Project(const Vertex& v, int screenWidth, int screenHeight) const;
};