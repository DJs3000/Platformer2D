#include "resources.hpp"

namespace {

[[nodiscard]] Platformer2D::Resources::backgrounds_table LoadBackgrounds();
[[nodiscard]] Platformer2D::Resources::foregrounds_table LoadForegrounds();
[[nodiscard]] Platformer2D::Resources::spritesets_table LoadSpritesets();

template <typename T>
[[nodiscard]] bool ValidateTable(T &table);

template <typename T, typename Func>
void DeleteTable(T& table, Func delete_function);

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
    Platformer2D::Resources::spritesets_table spritesets_table = {
        { "atlas", TLN_LoadSpriteset("atlas.png") },
        { "knight_idle", TLN_LoadSpriteset("knight_idle.png") }
    };
    const bool is_valid = ValidateTable(spritesets_table);
    if (!is_valid) {
        DeleteTable(spritesets_table, TLN_DeleteSpriteset);
        return {};
    }
    return spritesets_table;
}

template <typename T>
[[nodiscard]] bool ValidateTable(T &table)
{
    static_assert(std::is_same_v<typename T::value_type, std::pair<const typename T::key_type, typename T::mapped_type>>, 
                  "T must be an unordered_map-like container");
    
    for (const auto & [key, object] : table) {
        if (object == nullptr)
            return false;
    }
    return true;
}

template <typename T, typename Func>
void DeleteTable(T& table, Func cleanup_function) 
{
    static_assert(std::is_same_v<typename T::value_type, std::pair<const typename T::key_type, typename T::mapped_type>>, 
                  "T must be an unordered_map-like container");
    
    for (const auto & [key, object] : table)
        cleanup_function(object);

    table.clear();
}

} // namespace
