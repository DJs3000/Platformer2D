#include "player.hpp"

Player Player::Init(ResourceManager::Sprite &sprite, const Vector2 &position)
{
    return {
        .current_tag = sprite.tags["Idle"],
        .sprite      = sprite,
        .pos         = position,
    };
}

void Player::ProcessEvents(Player &player)
{
    if (IsKeyDown(KEY_A) == true) {
        if (player.state == State::IDLE) {
            player.current_tag = player.sprite.tags["Run"];
            player.state = State::RUNNING;
        }
        player.dir = Direction::LEFT;
        player.pos.x -= 45 * GetFrameTime();
    } else if (IsKeyReleased(KEY_A) == true) {
        player.state       = State::IDLE;
        player.current_tag = player.sprite.tags["Idle"]; 
    }

    if (IsKeyDown(KEY_D) == true) {
        if (player.state == State::IDLE) {
            player.current_tag = player.sprite.tags["Run"];
            player.state = State::RUNNING;
        }
        player.dir = Direction::RIGHT;
        player.pos.x += 45 * GetFrameTime();
    } else if (IsKeyReleased(KEY_D) == true) {
        player.state = State::IDLE;
        player.current_tag = player.sprite.tags["Idle"];
    }
}

void Player::Update(Player &player)
{
    UpdateAsepriteTag(&player.current_tag);
}

void Player::Draw(const Player &player)
{
    const bool      horizontal_flip = player.dir == Direction::LEFT ? true : false;
    Rectangle       rect            = player.sprite.slices.at("hitbox_1").bounds;
    
    if (horizontal_flip == true)
        rect.x = (rect.x + player.pos.x) + rect.width / 2;
    else
        rect.x += player.pos.x;

    rect.y += player.pos.y;

    DrawAsepriteTagVFlipped(player.current_tag, player.pos, horizontal_flip, false, WHITE);
    DrawRectangleLinesEx(rect, 0.5f, RED);
}
