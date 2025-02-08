#pragma once
#include <Tilengine.h>

struct Player {
    enum class State : uint8_t {
        IDLE,
        RUN,
        JUMP
    };
    
    enum class Direction : uint8_t {
        LEFT,
        RIGHT,
        UP,
        DOWN,
    };

    unsigned int x         = {};
    unsigned int y         = {};
    unsigned int sprite_id = {};
    
    TLN_Sequence  idle   = {};
    TLN_Sequence  run    = {};
    TLN_Sequence  jump   = {};
    
    TLN_Spriteset idle_spriteset = {};
    TLN_Spriteset run_spriteset  = {};
    TLN_Spriteset jump_spriteset = {};

    State        state     = {};
    Direction    direction = {};

    static Player Init(const unsigned int x, const unsigned int y);
    static void Update(Player &player);
    static void ProcessInput(Player &player);

    [[nodiscard]] static bool IsValid(const Player &player) noexcept
    { 
        return player.sprite_id != 0 &&
               player.idle      != nullptr && 
               player.run       != nullptr &&
               player.jump      != nullptr; 
    }
};
