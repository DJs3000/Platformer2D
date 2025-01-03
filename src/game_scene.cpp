#include "scenes.hpp"
#include "resource_manager.hpp"
#include "error.hpp"
#include "utils.hpp"

#include <cstdint>

namespace {

struct GameScene final {
    enum Layers : unsigned int {
        BACKGROUND,
        FOREGROUND
    };

    struct Player {
        int x = {};
        int y = {};
    };

    TLN_Sequence idle_sequence = {};
    TLN_Sequence skip_sequence = {};

    unsigned int world_width  = {};
    unsigned int world_height = {};
    unsigned int camera_x     = {};

    Player       player       = {};
};

[[nodiscard]] GameScene InitScene();     
[[nodiscard]] bool SetupWorld(GameScene &scene);
[[nodiscard]] bool SetupSequences(GameScene &scene);
[[nodiscard]] bool SetupPlayer(GameScene &scene);

void RunScene(GameScene &scene);
void DestroyScene(GameScene &scene);

} // namespace

Scenes::SceneMessage Scenes::RunGameScene()
{
    GameScene scene = InitScene();     
    if (scene.idle_sequence == nullptr)
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
    
    result = SetupSequences(scene);
    if (result == false)
        return {};
    
    result = SetupPlayer(scene);
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

bool SetupSequences(GameScene &scene)
{
    constexpr unsigned int sequence_delay = 6;

    scene.idle_sequence = TLN_CreateSpriteSequence(nullptr, 
                                                  ResourceManager::GetSpriteset("atlas"), 
                                                  "player-idle/player-idle-", 
                                                  sequence_delay);
    if (scene.idle_sequence == nullptr) {
        Error::LogLastError();
        DestroyScene(scene);
        return false; 
    }

    scene.skip_sequence = TLN_CreateSpriteSequence(nullptr, 
                                                  ResourceManager::GetSpriteset("atlas"), 
                                                  "player-skip/player-skip-", 
                                                  sequence_delay);
    if (scene.skip_sequence == nullptr) {
        Error::LogLastError();
        DestroyScene(scene);
        return false;
    }
    return true;
}

bool SetupPlayer(GameScene &scene)
{
    constexpr unsigned int  sprite_index              = 0;
    constexpr unsigned int  loop                      = 0;
    constexpr unsigned int  initial_player_position_x = 48;
    constexpr unsigned int  initial_player_position_y = 144;
    constexpr std::uint32_t flags                     = 0;

    scene.player.x = initial_player_position_x;
    scene.player.y = initial_player_position_y; 

	bool result = TLN_ConfigSprite(sprite_index, ResourceManager::GetSpriteset("atlas"), flags);
    if (result == false) {
        Error::LogLastError();
        DestroyScene(scene);
        return false;
    }

	result = TLN_SetSpriteAnimation(sprite_index, scene.idle_sequence, loop);
    if (result == false) {
        Error::LogLastError();
        DestroyScene(scene);
        return false;
    }

	result = TLN_SetSpriteWorldPosition(sprite_index, scene.player.x, scene.player.y);
    if (result == false) {
        Error::LogLastError();
        DestroyScene(scene);
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
		if (TLN_GetInput(INPUT_LEFT) && scene.camera_x > 0)
			scene.camera_x -= 3;
		else if (TLN_GetInput(INPUT_RIGHT) && scene.camera_x < scene.world_width - TLN_GetWidth())
			scene.camera_x += 3;

		if (scene.camera_x != old_camera_x)
		{
			TLN_SetWorldPosition(scene.camera_x, 0);
			old_camera_x = scene.camera_x;
		}
    }
}

void DestroyScene(GameScene &scene)
{
    TLN_ReleaseWorld();
    if (scene.idle_sequence != nullptr)
        Utils::TryDeleteSequence(scene.idle_sequence);
    if (scene.skip_sequence != nullptr)
        Utils::TryDeleteSequence(scene.skip_sequence);
}

} // namespace
