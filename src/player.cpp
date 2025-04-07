#include "player.hpp"

Player Player::Init(ResourceManager::Sprite &sprite, const Vector2 &position, TargetCamera &camera)
{
    return {
        .current_tag = sprite.tags["Idle"],
        .sprite      = sprite,
        .pos         = position,
        .camera      = &camera,
        .slice       = sprite.slices["hitbox_1"],
        .pad_slice   = sprite.slices["pad"],
        .hitbox      = sprite.slices["hitbox_1"].bounds,
        .pad         = sprite.slices["pad"].bounds,
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
        player.camera->is_dirty_x = true;
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
        player.camera->is_dirty_x = true; 
    } else if (IsKeyReleased(KEY_D) == true) {
        player.state = State::IDLE;
        player.current_tag = player.sprite.tags["Idle"];
    }
}

void Player::Update(Player &player)
{
    if (player.camera->is_dirty_x == true) {
        if (player.dir == Direction::LEFT)
            player.camera->camera.target.x -= 48 * GetFrameTime();
        else
            player.camera->camera.target.x += 48 * GetFrameTime();
        player.camera->is_dirty_x = false;
    }
    if (player.camera->is_dirty_y == true) {
        player.camera->camera.target.y += 128 * GetFrameTime();
        player.camera->is_dirty_y = false;
    }
    UpdateHitbox(player);
    UpdateAsepriteTag(&player.current_tag);
}

void Player::UpdateHitbox(Player &player)
{
    const Rectangle rect  = player.slice.bounds;
    const Rectangle pad_r = player.pad_slice.bounds;

    if (player.dir == Direction::LEFT)
        player.hitbox.x = (rect.x + player.pos.x) + rect.width / 2;
    else
        player.hitbox.x = rect.x + player.pos.x;
    player.hitbox.y = player.pos.y + rect.y;

    if (player.dir == Direction::LEFT)
        player.pad.x = (pad_r.x + player.pos.x) + pad_r.width / 2;
    else
        player.pad.x = pad_r.x + player.pos.x;
    player.pad.y = player.pos.y + pad_r.y;
}

void Player::Draw(const Player &player)
{
    const bool      horizontal_flip = player.dir == Direction::LEFT ? true : false;
    Rectangle       rect            = player.sprite.slices.at("hitbox_1").bounds;
    
    DrawAsepriteTagVFlipped(player.current_tag, player.pos, horizontal_flip, false, WHITE);
    DrawRectangleLinesEx(player.hitbox, 0.5f, RED);
    DrawRectangleLinesEx(player.pad, 0.5f, RED);
}
