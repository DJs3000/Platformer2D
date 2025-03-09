#pragma once
#include <raylib.h>

struct Aseprite;
struct AsepriteTag;

namespace Graphics {
    inline constexpr Rectangle render_area       = {0.f, 0.f, 320.f, 180.f};
    inline constexpr int       default_font_size = 14;

    [[nodiscard]] bool Init() noexcept;
    void Close() noexcept;

    [[nodiscard]] Vector2 GetCursorPosition() noexcept;
    void BeginRender() noexcept;
    void EndRender() noexcept;
}
