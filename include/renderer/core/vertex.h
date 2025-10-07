#pragma once

class Vertex{
public:
    float x, y, z;

    Vertex() : x(0.0f), y(0.0f), z(0.0f) {}
    Vertex(float xCoord, float yCoord, float zCoord) : x(xCoord), y(yCoord), z(zCoord) {};
};