#pragma once
#include <raylib-aseprite.h>
#include <cstdint>
#include "resource_manager.hpp"

struct Player {
    enum class Direction : std::uint8_t {
        LEFT,
        RIGHT
    };
    
    enum class State : std::uint8_t {
        IDLE,
        RUNNING,
    };

    AsepriteTag             current_tag = {};
    ResourceManager::Sprite sprite      = {};
    Vector2                 pos         = {};
    Direction               dir         = Direction::RIGHT; 
    State                   state       = State::IDLE;
    Camera2D                *camera     = nullptr;

    static Player Init(ResourceManager::Sprite &sprite, const Vector2 &position);
    static void ProcessEvents(Player &player);
    static void Update(Player &player);
    static void Draw(const Player &player);
};
