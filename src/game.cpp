#include "game.hpp"
#include "resources.hpp"
#include "error.hpp"
#include "scenes.hpp"

bool Platformer2D::Init()
{
    constexpr unsigned int width              = 424;
    constexpr unsigned int height             = 240;
    constexpr unsigned int background_layers  = 5;
    constexpr unsigned int sprites            = 8;
    constexpr unsigned int pallete_animations = 0;

    TLN_Engine engine = TLN_Init(width, 
                                  height, 
                                  background_layers, 
                                  sprites, 
                                  pallete_animations);
    if (engine == nullptr) {
        LogLastError();
        return false;
    }

    const bool is_window_created = TLN_CreateWindow(nullptr, CWF_FULLSCREEN);
    if (is_window_created == false) {
        LogLastError();
        TLN_Deinit();
        return false;
    }

	TLN_SetLoadPath("assets");
    TLN_DisableCRTEffect();
    return true;
}

void Platformer2D::Run()
{
    Resources resources     = LoadResources();
    Scene    *current_scene = RunGameScene;
    bool      running       = true;

    while(running) {
        SceneMessage message = current_scene(resources);
        switch(message) {
        case SceneMessage::ERROR:
            LogError("Main cycle error in scene");
            running = false;
            break;
        case SceneMessage::EXIT:
            running = false;
            break;
        }
    }
}

void Platformer2D::Close()
{
    TLN_DeleteWindow();
    TLN_Deinit();
}
