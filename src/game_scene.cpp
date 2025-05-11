#include "scenes.hpp"
#include "graphics.hpp"
#include "resource_manager.hpp"
#include "player.hpp"
#include "tilemap.hpp"
#include "physics_constants.hpp"
#include "system.hpp"

#include <raylib.h>
#include <raylib-aseprite.h>
#include <memory>
#include <box2d/box2d.h>

namespace {
    struct GameScene {
        ResourceManager::Map       map    = {};
        Camera2D                   camera = {};
        std::unique_ptr<Player>    player = {};
        b2WorldId                  world  = {};
        std::vector<Physics::Body> bodies = {};

        [[nodiscard]] static GameScene Init();
         
        static void ProcessEvents(GameScene &scene);
        static void Update(GameScene &scene);
        static void Draw(const GameScene &scene);
    };

    void DrawFloor();
}

Scenes::Message Scenes::RunGameScene()
{
    GameScene scene = GameScene::Init();
    ResourceManager::Sprite sprite = ResourceManager::GetSprite("player");
    scene.player  = std::make_unique<Player>();
    *scene.player = Player::Init(sprite, scene.map.player_spawn_point, scene.camera);
    scene.bodies  = Physics::InitObjects(Tilemap::GetObjectGroupFromLayer(scene.map.map, "boxes"), scene.world);
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
    Player::ProcessEvents(*scene.player);    
}

void GameScene::Update(GameScene &scene)
{
    constexpr int steps = 4;
    b2World_Step(scene.world, GetFrameTime(), steps);
    Player::Update(*scene.player);
    TmxObjectGroup group = Tilemap::GetObjectGroupFromLayer(scene.map.map, "boxes");
    Physics::Update(scene.bodies, group);
}

void GameScene::Draw(const GameScene &scene)
{
    Graphics::BeginRender();
        BeginMode2D(scene.camera);
            ClearBackground(BLACK);
            DrawTMX(scene.map.map, &scene.camera, 0, 0, WHITE);
            Player::Draw(*scene.player);
            Graphics::DrawDebugPhysicsEdges(scene.bodies);
        EndMode2D();
    Graphics::EndRender();
}

GameScene GameScene::Init()
{
    ResourceManager::Map map = ResourceManager::GetMap("cave");
    
    Camera2D camera = {};
    camera.zoom     = 2.f;
    camera.offset.x = Graphics::render_area.width / 2.f;
    camera.offset.y = Graphics::render_area.height / 2.f;
    camera.target   = map.player_spawn_point;

	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity.y = PhysicsConstants::gravity;

    return {
        .map    = map,
        .camera = camera,
	    .world  = b2CreateWorld(&world_def),
    };
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
