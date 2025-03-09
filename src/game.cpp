#include "game.hpp"
#include "graphics.hpp"
#include "scenes.hpp"
#include "resource_manager.hpp"
#include <cstdlib>

namespace {
    [[nodiscard]] bool Init();
    void Close();
}

int Platformer::Run()
{
    bool is_initialized = Init();
    if (is_initialized == false)
        return EXIT_FAILURE;
    
    Scenes::Message message = Scenes::RunGameScene();
    if (message == Scenes::Message::EXIT)
        Close();
    return EXIT_SUCCESS;
}

namespace {
    bool Init()
    {
        bool is_initialized = Graphics::Init();
        if (is_initialized == false)
            return false;
        
        is_initialized = ResourceManager::LoadResources();
        if (is_initialized == false)
            return false;

        SetExitKey(KEY_NULL);
        SetTargetFPS(120);
        return true;
    }

    void Close()
    {
        ResourceManager::UnloadResources();
        Graphics::Close();
    }
}
