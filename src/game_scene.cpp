#include "scenes.hpp"
#include "resource_manager.hpp"
#include "error.hpp"
#include "utils.hpp"
#include "player.hpp"

#include <cstdint>

namespace {

struct GameScene final {
    enum Layers : unsigned int {
        BACKGROUND,
        FOREGROUND
    };

    unsigned int world_width  = {};
    unsigned int world_height = {};
    unsigned int camera_x     = {};

    Player       player       = {};

    [[nodiscard]] static bool IsValid(const GameScene &scene) noexcept
    { return Player::IsValid(scene.player); }
};

[[nodiscard]] GameScene InitScene();     
[[nodiscard]] bool SetupWorld(GameScene &scene);
[[nodiscard]] bool SetupPlayer(Player &player);

void RunScene(GameScene &scene);
void DestroyScene(GameScene &scene);

} // namespace

Scenes::SceneMessage Scenes::RunGameScene()
{
    GameScene scene = InitScene();     
    if (GameScene::IsValid(scene) == false)
        return SceneMessage::ERROR;
    RunScene(scene);
    DestroyScene(scene);
    return SceneMessage::EXIT;
}

namespace {

GameScene InitScene()
{
    GameScene scene = {};

    bool result = SetupWorld(scene);
    if (result == false)
        return {};
    
    result = SetupPlayer(scene.player);
    if (result == false)
        return {};

    return scene;
}

bool SetupWorld(GameScene &scene)
{
    constexpr unsigned int first_layer = 0;
    const bool is_loaded = TLN_LoadWorld("map.tmx", first_layer);
    if (is_loaded == false) {
        Error::LogLastError();
        DestroyScene(scene);
        return false; 
    }
	scene.world_width  = TLN_GetLayerWidth(GameScene::FOREGROUND);
	scene.world_height = TLN_GetLayerHeight(GameScene::FOREGROUND);
    return true;
}

bool SetupPlayer(Player &player)
{
    constexpr unsigned int player_x = 28;
    constexpr unsigned int player_y = 114;

    player = Player::Init(player_x, player_y);
    if (Player::IsValid(player) == false) {
        Error::LogError("Can't initialize player!");
        return false;
    }
    return true;
}

void RunScene(GameScene &scene)
{
    unsigned int old_camera_x = 0;

	TLN_SetWorldPosition(scene.camera_x, 0);
    while(TLN_ProcessWindow()) {
        TLN_DrawFrame(0);
        Player::ProcessInput(scene.player);
    }
}

void DestroyScene(GameScene &scene)
{
    TLN_ReleaseWorld();
}

} // namespace
