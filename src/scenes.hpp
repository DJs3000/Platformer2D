#pragma once

namespace Platformer2D {

class Resources;

enum class SceneMessage {
    ERROR,
    EXIT
};

using Scene = SceneMessage(const Resources&);

[[nodiscard]] SceneMessage RunGameScene(const Resources &resources);

} // namespace Platformer2D 
