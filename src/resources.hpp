#pragma once
#include <unordered_map>
#include <Tilengine.h>
#include <string>

namespace Platformer2D {

class Resources final {
public:
    using backgrounds_table = std::unordered_map<std::string, TLN_Tilemap>;
    using foregrounds_table = std::unordered_map<std::string, TLN_Tilemap>; 
    using spritesets_table  = std::unordered_map<std::string, TLN_Spriteset>;

    Resources(backgrounds_table &&backgrounds,
              foregrounds_table &&foregrounds,
              spritesets_table  &&spritesets)
        : m_backgrounds(backgrounds)
        , m_foregrounds(foregrounds)
        , m_spritesets(spritesets) {}
    ~Resources()
    {
        for (auto & [key, spriteset] : m_spritesets)
            TLN_DeleteSpriteset(spriteset);
        for (auto & [key, background] : m_backgrounds)
            TLN_DeleteTilemap(background);
        for (auto & [key, foreground] : m_foregrounds)
            TLN_DeleteTilemap(foreground);
    }

    [[nodiscard]] TLN_Tilemap getBackground(const std::string &name) const
    { return m_backgrounds.at(name); }
    [[nodiscard]] TLN_Tilemap getForeground(const std::string &name) const
    { return m_foregrounds.at(name); }
    [[nodiscard]] TLN_Spriteset getSpriteset(const std::string &name) const
    { return m_spritesets.at(name); }
private:
    backgrounds_table m_backgrounds = {};
    foregrounds_table m_foregrounds = {};
    spritesets_table  m_spritesets  = {};
};

[[nodiscard]] Resources LoadResources();

} // namespace Plaftormer2D
