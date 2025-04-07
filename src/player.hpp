#pragma once
#include <raylib-aseprite.h>
#include <cstdint>

#include "camera.hpp"
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
    TargetCamera           *camera      = {};
    AsepriteSlice           slice       = {};
    AsepriteSlice           pad_slice   = {};
    Rectangle               hitbox      = {};
    Rectangle               pad         = {};

    static Player Init(ResourceManager::Sprite &sprite, const Vector2 &position, TargetCamera &camera);
    static void ProcessEvents(Player &player);
    static void Update(Player &player);
    static void UpdateHitbox(Player &player);
    static void Draw(const Player &player);
};
