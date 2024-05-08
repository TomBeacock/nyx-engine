#pragma once

#include "nyx/log.h"

#include <windows.h>

#include <exception>

namespace DX {
inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr)) {
        throw std::exception();
    }
}
}  // namespace DX