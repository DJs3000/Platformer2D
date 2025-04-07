#pragma once
#include <raylib.h>

struct TargetCamera {
    Camera2D camera     = {};
    bool     is_dirty_x = {};
    bool     is_dirty_y = {};
};
