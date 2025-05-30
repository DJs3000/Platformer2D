#pragma once
#include "graphics.hpp"

void UpdateCamera2D(Camera2D &camera, const Vector2 &target_position, const float map_width)
{
    constexpr float offset = 320;
    if (target_position.x - offset <= 0) {
        camera.target.x = offset;
        return;
    }
    if (target_position.x + offset >= map_width) {
        camera.target.x = map_width - offset;
        return;
    }
    camera.target.x = target_position.x;
    camera.target.y = target_position.y;
}
