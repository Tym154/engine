#pragma once

#include <cstdint>

struct Color{
    uint8_t r, g, b, a;

    Color() : r(255), g(255), b(255), a(255) {} // Default to white

    explicit Color(uint32_t argb) {
        a = (argb >> 24) & 0xFF;
        r = (argb >> 16) & 0xFF;
        g = (argb >> 8) & 0xFF;
        b = argb & 0xFF;
    }

    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) : r(red), g(green), b(blue), a(alpha) {}

    uint32_t ColorToUint32() const {
        return (a << 24) | (r << 16) | (g << 8) | b;
    }
};

