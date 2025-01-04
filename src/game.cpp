#include "game.hpp"
#include "resource_manager.hpp"
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
        Error::LogLastError();
        return false;
    }

    bool result = TLN_CreateWindow(nullptr, CWF_FULLSCREEN);
    if (result == false) {
        Error::LogLastError();
        TLN_Deinit();
        return false;
    }
	TLN_SetLoadPath("assets");
    result = ResourceManager::Init();
    if (result == false) {
        Error::LogLastError();
        TLN_Deinit();
        return false;
    }

    TLN_DisableCRTEffect();
    return true;
}

void Platformer2D::Run()
{
    Scenes::Scene *current_scene = Scenes::RunGameScene;
    bool           running       = true;

    while(running) {
        Scenes::SceneMessage message = current_scene();
        switch(message) {
        case Scenes::SceneMessage::ERROR:
            Error::LogError("Main cycle error in scene");
            running = false;
            break;
        case Scenes::SceneMessage::EXIT:
            running = false;
            break;
        }
    }
}

void Platformer2D::Close()
{
    ResourceManager::Close();
    TLN_DeleteWindow();
    TLN_Deinit();
}
