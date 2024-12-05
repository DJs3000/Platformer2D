#pragma once
#include <map>
#include <string>
#include <Tilengine.h>

namespace Platformer2D {
struct Player {
    enum class State {
        IDLE,
        WALKING
    };

    int   m_x             = {};
    int   m_y             = {};
    State m_current_state = State::IDLE;
private:
    std::map<State, TLN_Sequence> m_spritesets = {};
};

[[nodiscard]] bool SetPlayerSequence();
} // namespace Platformer2D
