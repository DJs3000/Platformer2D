#include "scenes.hpp"
#include "graphics.hpp"
#include "resource_manager.hpp"
#include "player.hpp"
#include "tilemap.hpp"
#include "physics_constants.hpp"
#include "system.hpp"
#include "camera.hpp"

#include <raylib.h>
#include <raylib-aseprite.h>
#include <memory>
#include <box2d/box2d.h>

namespace {
    struct GameScene {
        TmxMap                map           = {};
        Camera2D              camera        = {};
        Player                player        = {};
        b2WorldId             world         = {};
        Physics::ObjectsTable physics_table = {};
        bool                  debug_draw    = {};

        [[nodiscard]] static GameScene Init();
         
        static void ProcessEvents(GameScene &scene);
        static void Update(GameScene &scene);
        static void Draw(const GameScene &scene);
    };
}

Scenes::Message Scenes::RunGameScene()
{
    GameScene scene = GameScene::Init();
    while(!WindowShouldClose()) {
        GameScene::ProcessEvents(scene);
        GameScene::Update(scene);
        GameScene::Draw(scene);
    }
    b2DestroyWorld(scene.world);
    return Message::EXIT;
}

void GameScene::ProcessEvents(GameScene &scene)
{
    if (IsKeyDown(KEY_LEFT_SHIFT) == true) {
        if (IsKeyPressed(KEY_TWO) == true)
            scene.debug_draw = !scene.debug_draw;
    }
    Player::ProcessEvents(scene.player);    
}

void GameScene::Update(GameScene &scene)
{
    constexpr int steps     = 4; 
    const float   map_width = static_cast<float>(scene.map.tileWidth * scene.map.width);
    b2World_Step(scene.world, GetFrameTime(), steps);
    Player::Update(scene.player);
    Physics::Update(scene.map, scene.physics_table);
    UpdateCamera2D(scene.camera, scene.player.pos, map_width);
}

void GameScene::Draw(const GameScene &scene)
{
    Graphics::BeginRender();
        BeginMode2D(scene.camera);
            ClearBackground(BLACK);
            DrawTMX(&scene.map, &scene.camera, 0, 0, WHITE);
            Player::Draw(scene.player);
            if (scene.debug_draw)
                Graphics::DrawDebugPhysics(scene.physics_table);
        EndMode2D();
    Graphics::EndRender();
}

GameScene GameScene::Init()
{
    TmxMap                  map    = ResourceManager::GetMap("cave");
    ResourceManager::Sprite sprite = ResourceManager::GetSprite("player");

    Camera2D camera = {};
    camera.zoom     = 2.f;
    camera.offset.x = Graphics::render_area.width / 2.f;
    camera.offset.y = Graphics::render_area.height / 2.f;
    camera.target   = Tilemap::GetPlayerSpawnPosition(map);

	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity.y  = PhysicsConstants::gravity;
	b2WorldId world      = b2CreateWorld(&world_def);

    Player                player        = Player::Init(sprite, Tilemap::GetPlayerSpawnPosition(map));
    Physics::ObjectsTable physics_table = Physics::CreatePhysicsBodies(map, world);

    return {
        .map            = map,
        .camera         = camera,
        .player         = player, 
        .world          = world,
        .physics_table  = std::move(physics_table),
    };
}
