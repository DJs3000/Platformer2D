#pragma once

namespace Scenes {

enum class SceneMessage {
    ERROR,
    EXIT
};

using Scene = SceneMessage ();

[[nodiscard]] SceneMessage RunGameScene();

}
