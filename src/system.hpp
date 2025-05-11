#pragma once

namespace System {
    constexpr bool IsInDebugMode()
    {
        #ifdef NDEBUG
            return true;
        #endif
            return false;
    }
}
