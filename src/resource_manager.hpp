#pragma once
#include <unordered_map>
#include <Tilengine.h>
#include <string>

namespace ResourceManager {
    using backgrounds_table = std::unordered_map<std::string, TLN_Tilemap>;
    using foregrounds_table = std::unordered_map<std::string, TLN_Tilemap>; 
    using spritesets_table  = std::unordered_map<std::string, TLN_Spriteset>;
    
    [[nodiscard]] bool Init();
    void Close();

    [[nodiscard]] TLN_Tilemap GetBackground(const std::string &name);
    [[nodiscard]] TLN_Tilemap GetForeground(const std::string &name);
    [[nodiscard]] TLN_Spriteset GetSpriteset(const std::string &name);
}
