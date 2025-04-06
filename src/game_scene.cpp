#include "scenes.hpp"
#include "graphics.hpp"
#include "resource_manager.hpp"
#include "player.hpp"
#include "tilemap.hpp"
#include "physac.h"

#include <raylib.h>
#include <raylib-aseprite.h>
#include <memory>

namespace {
    struct GameScene {
        ResourceManager::Map    map    = {};
        TargetCamera            camera = {};
        Player                  player = {};
        PhysicsBody     floor  = {};

        [[nodiscard]] static GameScene Init();
         
        static void ProcessEvents(GameScene &scene);
        static void Update(GameScene &scene);
        static void Draw(const GameScene &scene);
    };
}

Scenes::Message Scenes::RunGameScene()
{
    GameScene scene = GameScene::Init();
    ResourceManager::Sprite sprite = ResourceManager::GetSprite("player");
    scene.player = Player::Init(sprite, scene.map.player_spawn_point, scene.camera);

    // Create obstacle circle physics body
    Vector2 circle_position    = {scene.player.pos.x, scene.player.pos.y};
    PhysicsBody circle         = CreatePhysicsBodyCircle(circle_position, 45, 10);
    while(!WindowShouldClose()) {
        GameScene::ProcessEvents(scene);
        GameScene::Update(scene);
        GameScene::Draw(scene);
    }
    // Draw created physics bodies
    int bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount; i++) {
        PhysicsBody body = GetPhysicsBody(i);
        DestroyPhysicsBody(body);
    }
    return Message::EXIT;
}

void GameScene::ProcessEvents(GameScene &scene)
{
   Player::ProcessEvents(scene.player);
}

void GameScene::Update(GameScene &scene)
{
    // TODO: Fix collision offset
    Player::Update(scene.player);
    bool is_collided = CheckCollisionTMXObjectGroupRec(Tilemap::GetObjectGroupFromLayer(scene.map.map, "collision"), 
                                                       scene.player.hitbox, 
                                                       nullptr);
    if (is_collided == false) {
        scene.player.pos.y += GetFrameTime() * 128;
        scene.player.camera->is_dirty_y = true;
    }
}

void GameScene::Draw(const GameScene &scene)
{
    Graphics::BeginRender();
        BeginMode2D(scene.camera.camera);
            ClearBackground(BLACK);
            DrawTMX(scene.map.map, &scene.camera.camera, 0, 0, WHITE);
            Player::Draw(scene.player);
            TmxObjectGroup      collision_group = Tilemap::GetObjectGroupFromLayer(scene.map.map, "collision");
            TmxObject           floor_obj       = Tilemap::GetObjectFromGroup(collision_group, "floor_0");
            Rectangle           floor_rect      = {floor_obj.x, floor_obj.y, floor_obj.width, floor_obj.height};
            DrawRectangleRec(floor_rect, RED);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                constexpr float width = 30;
                constexpr float height = 10;
                constexpr  float density = 150;
                Vector2 position = GetScreenToWorld2D(Graphics::GetCursorPosition(), scene.camera.camera);
                CreatePhysicsBodyRectangle(position, width, height, density);
            } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                constexpr float width = 30;
                constexpr float height = 10;
                constexpr  float density = 10;
                Vector2 position = GetScreenToWorld2D(Graphics::GetCursorPosition(), scene.camera.camera);
                CreatePhysicsBodyCircle(position, 20.f, density);
            }
            // Draw created physics bodies
            int bodiesCount = GetPhysicsBodiesCount();
            for (int i = 0; i < bodiesCount; i++)
            {
                PhysicsBody body = GetPhysicsBody(i);

                if (body != NULL)
                {
                    int vertexCount = GetPhysicsShapeVerticesCount(i);
                    for (int j = 0; j < vertexCount; j++)
                    {
                        // Get physics bodies shape vertices to draw lines
                        // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                        Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                        Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                        DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
                    }
                }
            }
        EndMode2D();
    Graphics::EndRender();
}

GameScene GameScene::Init()
{
    ResourceManager::Map    map    = ResourceManager::GetMap("cave");
    
    Camera2D camera = {};
    camera.zoom     = 2.f;
    camera.offset.x = Graphics::render_area.width / 2.f;
    camera.offset.y = Graphics::render_area.height / 2.f;
    camera.target   = map.player_spawn_point;

    TmxObjectGroup      collision_group = Tilemap::GetObjectGroupFromLayer(map.map, "collision");
    TmxObject           floor_obj       = Tilemap::GetObjectFromGroup(collision_group, "floor_0");
    Rectangle           floor_rect      = {(floor_obj.x + floor_obj.width) / 2, (floor_obj.y + floor_obj.height / 2), floor_obj.width, floor_obj.height};
    PhysicsBody floor_body      = CreatePhysicsBodyRectangle({floor_rect.x, floor_rect.y}, floor_rect.width, floor_rect.height, 100);
    floor_body->enabled = false; // make it static
                                
    return {
        .map    = map,
        .camera = {camera},
        .floor  = floor_body,
    };
}
