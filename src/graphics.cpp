#include <raylib.h>
#include <algorithm>
#include "graphics.hpp" 

namespace {
    RenderTexture   target_texture  = {};
    Vector2         cursor_position = {};
}

bool Graphics::Init() noexcept
{
    constexpr Rectangle window_size = {0.f, 0.f, 1280.f, 800.f};
    constexpr const char *window_title = "Platformer";
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(window_size.width, window_size.height, window_title);
    if (IsWindowReady() == false)
        return false;

    target_texture = LoadRenderTexture(render_area.width, render_area.height);
    if (IsRenderTextureValid(target_texture) == false)
        return false;

    SetTextureFilter(target_texture.texture, TEXTURE_FILTER_POINT);
    return true;
}

Vector2 Graphics::GetCursorPosition() noexcept
{
    return cursor_position;
}

void Graphics::BeginRender() noexcept
{
    const float mouse_x = static_cast<float>(GetMouseX());
    const float mouse_y = static_cast<float>(GetMouseY());
    const float width   = static_cast<float>(GetScreenWidth());
    const float height  = static_cast<float>(GetScreenHeight());

    cursor_position.x = mouse_x * render_area.width / width;
    cursor_position.y = mouse_y * render_area.height / height;
    BeginTextureMode(target_texture);
}

void Graphics::EndRender() noexcept
{
    EndTextureMode();
    BeginDrawing();
        ClearBackground(BLACK);
        const Rectangle source_rect = { 
            0.f, 0.f, 
            render_area.width,
            -render_area.height
        };
        const Rectangle dest_rect {
            0.f, 0.f,
            static_cast<float>(GetScreenWidth()), 
            static_cast<float>(GetScreenHeight())
        };
        DrawTexturePro(target_texture.texture, source_rect, dest_rect, {}, 0.f, 
                       WHITE);
    EndDrawing();
}

void Graphics::Close() noexcept
{
    if (IsWindowReady() == true) {
        UnloadRenderTexture(target_texture);
        CloseWindow();
    }
}

void Graphics::DrawDebugPhysicsEdges(const std::vector<Physics::Body> &bodies)
{
    for (const auto &body : bodies) {
        // The boxes were created centered on the bodies, but raylib draws textures starting at the top left corner.
        // b2Body_GetWorldPoint gets the top left corner of the box accounting for rotation.
        b2Vec2 p = b2Body_GetWorldPoint(body.id, {-body.extent.x, -body.extent.y});
        b2Rot  rotation = b2Body_GetRotation(body.id);
        float  radians = b2Rot_GetAngle(rotation);

        Vector2 ps = {p.x, p.y};

        // I used these circles to ensure the coordinates are correct
        DrawCircleV(ps, 5.0f, GREEN);
        p = b2Body_GetWorldPoint(body.id, {0.0f, 0.0f});
        ps = {p.x, p.y};
        DrawCircleV(ps, 5.0f, BLUE);
        p = b2Body_GetWorldPoint(body.id, {body.extent.x, body.extent.y});
        ps = {p.x, p.y};
        DrawCircleV(ps, 5.0f, RED);
    }
}
