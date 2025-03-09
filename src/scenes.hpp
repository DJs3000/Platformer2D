#pragma once
#include <cstdint>

namespace Scenes {
    enum class Message : std::uint8_t {
        EXIT
    };

    [[nodiscard]] Message RunGameScene();
}
