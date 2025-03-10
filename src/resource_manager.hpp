#pragma once
#include <string>
#include <vector>
#include <raylib-aseprite.h>
#include <map>

typedef struct tmx_map TmxMap;

namespace ResourceManager {
    struct Sprite {
        struct Info {
            std::string               name   = {};
            std::string               path   = {};
            std::vector<std::string>  tags   = {}; 
            std::vector<std::string>  slices = {};
        };
    
        Aseprite                             aseprite = {};
        std::map<std::string, AsepriteTag>   tags     = {};
        std::map<std::string, AsepriteSlice> slices   = {};
    };
    
    struct Map {
        TmxMap *map                = {};
        Vector2 player_spawn_point = {};
    };

    [[nodiscard]] bool LoadResources();
    void UnloadResources();

    [[nodiscard]] Sprite GetSprite(const std::string &resource_name);
    [[nodiscard]] Map GetMap(const std::string &map_name);
}
