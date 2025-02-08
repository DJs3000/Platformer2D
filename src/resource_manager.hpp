#pragma once
#include <unordered_map>
#include <Tilengine.h>
#include <string>

namespace ResourceManager {
    [[nodiscard]] bool Init();
    void Close();

    [[nodiscard]] TLN_Tilemap GetBackground(const std::string &name);
    [[nodiscard]] TLN_Tilemap GetForeground(const std::string &name);
    [[nodiscard]] TLN_Spriteset GetSpriteset(const std::string &name);
    [[nodiscard]] TLN_Sequence GetSequence(const std::string &sequence_pack,
                                           const std::string &name);

    [[nodiscard]] inline unsigned int GenerateSpriteIndex() noexcept
    {
        static unsigned int sprite_id;
        ++sprite_id;
        return sprite_id;
    }
}
