#include "scenes.hpp"
#include "graphics.hpp"
#include "resource_manager.hpp"
#include "player.hpp"

#include <raylib.h>
#include <raylib-aseprite.h>

struct GameScene {
    Player player = {};

    [[nodiscard]] static GameScene Init()
    {
        constexpr Vector2 player_pos = {
            .x = Graphics::render_area.width / 4,
            .y = Graphics::render_area.height / 16,
        };
        ResourceManager::Sprite sprite = ResourceManager::GetSprite("player");
        return {
            .player = Player::Init(sprite, player_pos),
        };
    }
     
    static void ProcessEvents(GameScene &scene);
    static void Update(GameScene &scene);
    static void Draw(const GameScene &scene);
};

namespace {
    void DrawFloor();
}

Scenes::Message Scenes::RunGameScene()
{
    GameScene scene = GameScene::Init();
    while(!WindowShouldClose()) {
        GameScene::ProcessEvents(scene);
        GameScene::Update(scene);
        GameScene::Draw(scene);
    }
    return Message::EXIT;
}

void GameScene::ProcessEvents(GameScene &scene)
{
    Player::ProcessEvents(scene.player);    
}

void GameScene::Update(GameScene &scene)
{
    Player::Update(scene.player);
}

void GameScene::Draw(const GameScene &scene)
{
    Graphics::BeginRender();
        ClearBackground(BLACK);
        DrawFloor();
        Player::Draw(scene.player);
    Graphics::EndRender();
}

namespace {
    void DrawFloor()
    {
        constexpr Rectangle floor_rect = {
            .x = 0,
            .y = Graphics::render_area.height / 2,
            .width = Graphics::render_area.width,
            .height = Graphics::render_area.height / 2,
        };
        DrawRectangleRec(floor_rect, GREEN);
    }
}
