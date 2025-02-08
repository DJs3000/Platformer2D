#include "player.hpp"
#include "resource_manager.hpp"
#include "error.hpp"

namespace {
    void ChangeDirectionAndFlipSprite(Player &player, const Player::Direction new_direction, const bool flip_sprite);
    void SetStateAndAnimation(Player &player, const Player::State new_state);
}

Player Player::Init(const unsigned int x, const unsigned int y)
{
    Player player = {
        .x              = x,
        .y              = y,
        .sprite_id      = ResourceManager::GenerateSpriteIndex(),
        .idle           = ResourceManager::GetSequence("knight", "idle"),
        .run            = ResourceManager::GetSequence("knight", "run"),
        .jump           = ResourceManager::GetSequence("knight", "jump"),
        .idle_spriteset = ResourceManager::GetSpriteset("knight_idle"),
        .run_spriteset  = ResourceManager::GetSpriteset("knight_run"),
        .jump_spriteset = ResourceManager::GetSpriteset("knight_jump"),
        .state          = State::IDLE,
        .direction      = Direction::RIGHT,
    };
    
    bool result = TLN_SetSpriteSet(player.sprite_id, ResourceManager::GetSpriteset("knight_idle"));
    if (result == false) {
        Error::LogLastError();
        return {};
    }

	result = TLN_SetSpriteAnimation(player.sprite_id, player.idle, 0);
    if (result == false) {
        Error::LogLastError();
        return {};
    }

	result = TLN_SetSpriteWorldPosition(player.sprite_id, player.x, player.y);
    if (result == false) {
        Error::LogLastError();
        return {};
    }
    
    return player;
}

void Player::ProcessInput(Player &player)
{
//    if (TLN_GetInput(INPUT_LEFT) && scene.camera_x > 0)
//        scene.camera_x -= 3;
//    else if (TLN_GetInput(INPUT_RIGHT) && scene.camera_x < scene.world_width - TLN_GetWidth())
//        scene.camera_x += 3;
//
//    if (scene.camera_x != old_camera_x)
//    {
//        TLN_SetWorldPosition(scene.camera_x, 0);
//        old_camera_x = scene.camera_x;
//    }
    if (TLN_GetInput(INPUT_LEFT) == true) {
        ChangeDirectionAndFlipSprite(player, Direction::LEFT, true);
        SetStateAndAnimation(player, State::RUN);
    } else if (TLN_GetInput(INPUT_RIGHT) == true) {
        ChangeDirectionAndFlipSprite(player, Direction::RIGHT, false);
        SetStateAndAnimation(player, State::RUN);
    } else if (TLN_GetInput(INPUT_UP) == true) {
        SetStateAndAnimation(player, State::JUMP);
    } else {
        SetStateAndAnimation(player, State::IDLE);
    }
}

void Player::Update(Player &player)
{

}

namespace {

void ChangeDirectionAndFlipSprite(Player &player, const Player::Direction new_direction, const bool flip_sprite)
{
    if (player.direction != new_direction) {
        TLN_EnableSpriteFlag(player.sprite_id, FLAG_FLIPX, flip_sprite);
        player.direction = new_direction;
    }
}

void SetStateAndAnimation(Player &player, const Player::State new_state)
{
    if (player.state != new_state) {
        switch(new_state) {
        case Player::State::IDLE:
            TLN_SetSpriteAnimation(player.sprite_id, player.idle, 0);
            TLN_SetSpriteSet(player.sprite_id, ResourceManager::GetSpriteset("knight_idle"));
            player.state = Player::State::IDLE;
            break;
        case Player::State::RUN:
            TLN_SetSpriteAnimation(player.sprite_id, player.run, 0);
            TLN_SetSpriteSet(player.sprite_id, ResourceManager::GetSpriteset("knight_run"));
            player.state = Player::State::RUN;
            break;
        case Player::State::JUMP:
            TLN_SetSpriteAnimation(player.sprite_id, player.jump, 0);
            TLN_SetSpriteSet(player.sprite_id, ResourceManager::GetSpriteset("knight_jump"));
            player.state = Player::State::JUMP;
            break;
        default:
            break;
        }
    }
}

} // namespace
