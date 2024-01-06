#ifndef UNICODE
#define UNICODE
#endif

#include "nyx/init.h"

#include <windows.h>

#include <iostream>

namespace Nyx {
LRESULT CALLBACK window_proc(
    HWND window, UINT msg, WPARAM w_param, LPARAM l_param);

void launch(int argc, char **argv)
{
    HINSTANCE instance = GetModuleHandle(nullptr);

    // Window class
    const wchar_t *CLASS_NAME = L"Main Window";
    WNDCLASS window_class = {
        .lpfnWndProc = window_proc,
        .hInstance = instance,
        .lpszClassName = CLASS_NAME,
    };
    RegisterClass(&window_class);

    // Create window
    HWND window = CreateWindowEx(0, CLASS_NAME, L"Sample Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, nullptr, nullptr, instance, nullptr);
    if (window == nullptr) {
        return;
    }

    // Show window
    STARTUPINFO startup_info{};
    GetStartupInfo(&startup_info);
    int cmd_show = SW_SHOWDEFAULT;
    if (startup_info.dwFlags & STARTF_USESHOWWINDOW) {
        cmd_show = startup_info.wShowWindow;
    }
    ShowWindow(window, cmd_show);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK window_proc(
    HWND window, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(window, msg, w_param, l_param);
}
}  // namespace Nyx
