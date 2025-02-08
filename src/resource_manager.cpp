#include "resource_manager.hpp"
#include "error.hpp"

namespace {
using backgrounds_table   = std::unordered_map<std::string, TLN_Tilemap>;
using foregrounds_table   = std::unordered_map<std::string, TLN_Tilemap>; 
using spritesets_table    = std::unordered_map<std::string, TLN_Spriteset>;
using sequencepacks_table = std::unordered_map<std::string, TLN_SequencePack>;
   
[[nodiscard]] backgrounds_table LoadBackgrounds();
[[nodiscard]] foregrounds_table LoadForegrounds();
[[nodiscard]] spritesets_table LoadSpritesets();
[[nodiscard]] sequencepacks_table LoadSequencePacks();

backgrounds_table   backgrounds     = {};
foregrounds_table   foregrounds     = {}; 
spritesets_table    spritesets      = {};
sequencepacks_table sequences_packs = {};
} // namespace

bool ResourceManager::Init()
{
    backgrounds     = LoadBackgrounds();
    foregrounds     = LoadForegrounds();
    spritesets      = LoadSpritesets();
    sequences_packs = LoadSequencePacks();
      
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
    for (auto & [key, sequence_pack] : sequences_packs)
        TLN_DeleteSequencePack(sequence_pack);
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
    try {
        TLN_Spriteset spriteset = spritesets.at(name);
        return spriteset;
    } catch(const std::exception &ex) {
        Error::LogError(ex.what() + std::string{" | Can't get a spriteset: "} + name);
        return nullptr;
    }
}

TLN_Sequence ResourceManager::GetSequence(const std::string &sequence_pack,
                                          const std::string &name)
{
	return TLN_FindSequence(sequences_packs.at(sequence_pack), name.c_str());
}

namespace {

backgrounds_table LoadBackgrounds()
{
    return {};
}

foregrounds_table LoadForegrounds()
{
    return {};
}

spritesets_table LoadSpritesets()
{
    return {
        { "knight_idle", TLN_LoadSpriteset("knight/knight_idle.png") },
        { "knight_run", TLN_LoadSpriteset("knight/knight_run.png") },
        { "knight_jump", TLN_LoadSpriteset("knight/knight_jump.png") },
    };
}

sequencepacks_table LoadSequencePacks()
{
    return {
        { "knight", TLN_LoadSequencePack("knight/knight.sqx") },
    };
}

} // namespace
