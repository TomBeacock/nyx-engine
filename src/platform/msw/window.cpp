#include "window.h"

#include "nyx/event.h"
#include "string_util.h"

std::unique_ptr<Nyx::Window> Nyx::Window::create()
{
    return std::make_unique<Nyx::MSW::Window>();
}

Nyx::MSW::Window::Window()
{
    // Window class
    WNDCLASS window_class = {
        .lpfnWndProc = Nyx::MSW::Window::proc,
        .hInstance = GetModuleHandle(nullptr),
        .lpszClassName = L"Main Window",
    };
    RegisterClass(&window_class);

    // Create window
    this->handle = CreateWindowEx(0, L"Main Window", L"Sample Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), this);
}

Nyx::MSW::Window::~Window()
{
    DestroyWindow(this->handle);
}

void Nyx::MSW::Window::show()
{
    ShowWindow(this->handle, SW_SHOWDEFAULT);
}

void Nyx::MSW::Window::minimise()
{
    WINDOWPLACEMENT placement{
        .length = sizeof(WINDOWPLACEMENT),
        .showCmd = SW_MINIMIZE,
    };
    SetWindowPlacement(this->handle, &placement);
}

void Nyx::MSW::Window::maximise()
{
    WINDOWPLACEMENT placement{
        .length = sizeof(WINDOWPLACEMENT),
        .showCmd = SW_MAXIMIZE,
    };
    SetWindowPlacement(this->handle, &placement);
}

void Nyx::MSW::Window::restore()
{
    WINDOWPLACEMENT placement{
        .length = sizeof(WINDOWPLACEMENT),
        .showCmd = SW_RESTORE,
    };
    SetWindowPlacement(this->handle, &placement);
}

bool Nyx::MSW::Window::poll_event(Event &event)
{
    MSG msg{};
    if (PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE)) {
        this->event = &event;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        return true;
    }
    return false;
}

void Nyx::MSW::Window::set_title(const std::u8string &title)
{
    std::wstring wide_title = Nyx::MSW::utf8_to_wstring(title);
    SetWindowText(this->handle, wide_title.c_str());
}

LRESULT Nyx::MSW::Window::proc(
    HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    Nyx::MSW::Window *window = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT *create = (CREATESTRUCT *)l_param;
        window = (Nyx::MSW::Window *)create->lpCreateParams;
        SetWindowLongPtr(wnd, GWLP_USERDATA, (LONG_PTR)window);
        window->handle = wnd;
    } else {
        window = (Nyx::MSW::Window *)GetWindowLongPtr(wnd, GWLP_USERDATA);
    }
    if (window != nullptr) {
        return window->handle_message(msg, w_param, l_param);
    } else {
        return DefWindowProc(wnd, msg, w_param, l_param);
    }
}

LRESULT Nyx::MSW::Window::handle_message(
    UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) {
        case WM_CLOSE: {
            this->event->set_type(Event::Close);
            return 0;
        }
    }
    return DefWindowProc(this->handle, msg, w_param, l_param);
}