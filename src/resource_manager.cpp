#include "resource_manager.hpp"

namespace {

[[nodiscard]] ResourceManager::backgrounds_table LoadBackgrounds();
[[nodiscard]] ResourceManager::foregrounds_table LoadForegrounds();
[[nodiscard]] ResourceManager::spritesets_table LoadSpritesets();

ResourceManager::backgrounds_table backgrounds = {};
ResourceManager::foregrounds_table foregrounds = {}; 
ResourceManager::spritesets_table  spritesets  = {};

} // namespace

bool ResourceManager::Init()
{
    backgrounds = LoadBackgrounds();
    foregrounds  = LoadForegrounds();
    spritesets  = LoadSpritesets();
    return true;
}

void ResourceManager::Close()
{
    for (auto & [key, spriteset] : spritesets)
        TLN_DeleteSpriteset(spriteset);
    for (auto & [key, background] : backgrounds)
        TLN_DeleteTilemap(background);
    for (auto & [key, foreground] : foregrounds)
        TLN_DeleteTilemap(foreground);
}

TLN_Tilemap ResourceManager::GetBackground(const std::string &name)
{
    return backgrounds.at(name);
}

TLN_Tilemap ResourceManager::GetForeground(const std::string &name)
{
    return foregrounds.at(name);
}

TLN_Spriteset ResourceManager::GetSpriteset(const std::string &name)
{
    return spritesets.at(name);
}

namespace {

ResourceManager::backgrounds_table LoadBackgrounds()
{
    return {};
}

ResourceManager::foregrounds_table LoadForegrounds()
{
    return {};
}

ResourceManager::spritesets_table LoadSpritesets()
{
    return {
        { "atlas", TLN_LoadSpriteset("atlas.png") },
    };
}

} // namespace
