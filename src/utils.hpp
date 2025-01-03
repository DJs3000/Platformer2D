#pragma once
#include <Tilengine.h>
#include "error.hpp"

namespace Utils {
    inline void TryDeleteSequence(TLN_Sequence sequence)
    {
        const TLN_Error saved_last_error = TLN_GetLastError();       // We need to save last error, because next function call can overwrite it
        const bool result = TLN_DeleteSequence(sequence); // Yeah, we need to check for sequence deletion, because we can pass invalid object(no, I don't mean nullptr, I mean by internal Tilengine type)
        if (result == false)                                         // Well, I guess we can't fail here anyway, but still, who knows, maybe after some time this can fuck us
            Error::LogLastError();
        if (saved_last_error != TLN_ERR_OK)
            TLN_SetLastError(saved_last_error);                      // Restore error state
    }
}
