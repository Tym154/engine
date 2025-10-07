#include <cmath>

#include <renderer/camera.h>

static inline float toRadians(float deg) { return deg * 3.14159265f / 180.0f; }

Camera::Camera(float x, float y, float z, float init_pitch, float init_yaw, float init_roll, float focal_lenght) : position{x, y, z}, pitch(init_pitch), yaw(init_yaw), roll(init_roll), focal_length(focal_lenght) {};

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

    // apply yaw (y axis rotation)
    float cos_y = std::cos(yaw);
    float sin_y = std::sin(yaw);
    float x1 =  x * cos_y - z * sin_y;
    float z1 =  x * sin_y + z * cos_y;
    float y1 =  y;

    // apply pitch (x axis rotation)
    float cos_p = std::cos(pitch);
    float sin_p = std::sin(pitch);
    float y2 = y1 * cos_p - z1 * sin_p;
    float z2 = y1 * sin_p + z1 * cos_p;
    float x2 = x1;

    // apply roll (z axis rotation)
    float cos_r = std::cos(roll);
    float sin_r = std::sin(roll);
    float x3 = x2 * cos_r - y2 * sin_r;
    float y3 = x2 * sin_r + y2 * cos_r;
    float z3 = z2;

    return Vertex(x3, y3, z3);
}

void Camera::CameraMovement(float moveSpeed, float mouseSensitivity){
    // --- Handle keyboard input ---
    const bool* state = SDL_GetKeyboardState(nullptr);

    // Camera movement direction vector (forward/right/up)
    float forwardX = std::sin(yaw) * std::cos(pitch);
    float forwardY = std::sin(pitch);
    float forwardZ = std::cos(yaw) * std::cos(pitch);

    // Right vector (perpendicular to forward)
    float rightX = std::cos(yaw);
    float rightY = 0.0f;
    float rightZ = -std::sin(yaw);

    // Up vector (you could also compute from cross products if needed)
    float upX = 0.0f, upY = 1.0f, upZ = 0.0f;

    float moveX = 0.0f, moveY = 0.0f, moveZ = 0.0f;

    // Forward / Backward
    if (state[SDL_SCANCODE_W]) {
        moveX += forwardX * moveSpeed;
        moveY += forwardY * moveSpeed;
        moveZ += forwardZ * moveSpeed;
    }
    if (state[SDL_SCANCODE_S]) {
        moveX -= forwardX * moveSpeed;
        moveY -= forwardY * moveSpeed;
        moveZ -= forwardZ * moveSpeed;
    }

    // Strafe Left / Right
    if (state[SDL_SCANCODE_A]) {
        moveX -= rightX * moveSpeed;
        moveY -= rightY * moveSpeed;
        moveZ -= rightZ * moveSpeed;
    }
    if (state[SDL_SCANCODE_D]) {
        moveX += rightX * moveSpeed;
        moveY += rightY * moveSpeed;
        moveZ += rightZ * moveSpeed;
    }

    // Vertical movement (independent)
    if (state[SDL_SCANCODE_SPACE]) moveY += moveSpeed;
    if (state[SDL_SCANCODE_LCTRL]) moveY -= moveSpeed;

    Move(moveX, moveY, moveZ);

    // --- Handle mouse look ---
    float mouseX = 0.0f, mouseY = 0.0f;
    SDL_GetRelativeMouseState(&mouseX, &mouseY);

    pitch -= mouseY * mouseSensitivity;
    yaw   += mouseX * mouseSensitivity;

    // Clamp pitch
    const float pitchLimit = 1.5f;
    if (pitch > pitchLimit) pitch = pitchLimit;
    if (pitch < -pitchLimit) pitch = -pitchLimit;
}