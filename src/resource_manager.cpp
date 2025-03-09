#include <raylib-aseprite.h>
#include <unordered_map>
#include "resource_manager.hpp"

namespace {
    std::unordered_map<std::string, ResourceManager::Sprite> sprites_table = {};

    [[nodiscard]] bool LoadSprite(ResourceManager::Sprite::Info &&info, std::string &&resource_name);
}

bool ResourceManager::LoadResources()
{
    Sprite::Info player_sprite = {
        .name = "player",
        .path = "assets/knight/player.aseprite",
        .tags = {
            "Idle",
            "Run",
        },
        .slices = {
            "hitbox_1",
        },
    };
    bool loaded = LoadSprite(std::move(player_sprite), "player");
    return loaded;
}

void ResourceManager::UnloadResources()
{
    for (auto &[key, sprite] : sprites_table)
        UnloadAseprite(sprite.aseprite);
}

ResourceManager::Sprite ResourceManager::GetSprite(const std::string &resource_name)
{
    try {
        Sprite sprite = sprites_table.at(resource_name);
        return sprite;
    } catch(std::exception &ex) {
        TraceLog(LOG_ERROR, ex.what());
        return {};
    }
}

namespace {
    bool LoadSprite(ResourceManager::Sprite::Info &&info, std::string &&resource_name)
    {
        ResourceManager::Sprite sprite   = {};
        sprite.aseprite                  = LoadAseprite(info.path.c_str());  
        if (IsAsepriteValid(sprite.aseprite) == false)
            return false;

        if (info.tags.empty() == false) {
            for (auto &&tag_name : info.tags) {
                AsepriteTag tag = LoadAsepriteTag(sprite.aseprite, tag_name.c_str());
                if (IsAsepriteTagValid(tag) == false) {
                    TraceLog(LOG_ERROR, "Can't load tag in sprite");                
                    continue;
                }
                sprite.tags.insert({std::move(tag_name), tag});
            }
        }
        if (info.slices.empty() == false) {
            for (const auto &slice_name : info.slices) {
                AsepriteSlice slice = LoadAsepriteSlice(sprite.aseprite, slice_name.c_str());
                if (IsAsepriteSliceValid(slice) == false) {
                    TraceLog(LOG_ERROR, "Can't load slice in sprite");
                    continue;
                }
                sprite.slices.insert({std::move(slice_name), slice});
            }
        }
        sprites_table.insert({std::move(resource_name), std::move(sprite)});
        return true;
    }
}
