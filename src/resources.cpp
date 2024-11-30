#include "resources.hpp"

namespace {

[[nodiscard]] Platformer2D::Resources::backgrounds_table LoadBackgrounds();
[[nodiscard]] Platformer2D::Resources::foregrounds_table LoadForegrounds();
[[nodiscard]] Platformer2D::Resources::spritesets_table LoadSpritesets();

} // namespace

Platformer2D::Resources Platformer2D::LoadResources()
{
    return {
        std::move(LoadBackgrounds()),
        std::move(LoadForegrounds()),
        std::move(LoadSpritesets())
    };
}

namespace {

Platformer2D::Resources::backgrounds_table LoadBackgrounds()
{
    return {};
}

Platformer2D::Resources::foregrounds_table LoadForegrounds()
{
    return {};
}

Platformer2D::Resources::spritesets_table LoadSpritesets()
{
    return {
        { "atlas", TLN_LoadSpriteset("atlas.png") },
    };
}

} // namespace
