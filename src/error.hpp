#pragma once
#include <Tilengine.h>
#include <iostream>

namespace Error {
    inline void LogLastError()
    {
        const TLN_Error last_error = TLN_GetLastError();
        if (last_error != TLN_ERR_OK)
            std::cerr << TLN_GetErrorString(last_error) << std::endl;
    }

    inline void LogError(const std::string &error)
    {
        std::cerr << error << std::endl;
    }
}
