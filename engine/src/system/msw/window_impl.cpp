#include "window_impl.h"

#include "code_translation.h"
#include "nyx/events.h"
#include "nyx/string/string_util.h"

#include <array>
#include <iostream>
#include <vector>

constexpr USHORT mouse_wheel_event_flags = 0x0C00;
constexpr USHORT mouse_button_down_event_flags = 0x0155;
constexpr USHORT mouse_button_up_event_flags = 0x02AA;

namespace Nyx::MSW {
WindowImpl::WindowImpl()
{
    // WindowImpl class
    WNDCLASS window_class = {
        .lpfnWndProc = Nyx::MSW::WindowImpl::proc,
        .hInstance = GetModuleHandle(nullptr),
        .lpszClassName = L"Main Window",
    };
    RegisterClass(&window_class);

    // Create window
    this->handle = CreateWindowEx(0, L"Main Window", L"Sample Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), this);

    // Set initial cursor
    this->last_cursor = LoadCursor(nullptr, IDC_ARROW);

    // Register raw input devices
    std::array<RAWINPUTDEVICE, 2> devices = {
        RAWINPUTDEVICE{
            .usUsagePage = 0x0001,
            .usUsage = 0x0002,  // Generic mouse
            .dwFlags = 0,
            .hwndTarget = 0,
        },
        RAWINPUTDEVICE{
            .usUsagePage = 0x0001,
            .usUsage = 0x0006,  // Generic keyboard
            .dwFlags = 0,
            .hwndTarget = 0,
        },
    };

    if (RegisterRawInputDevices(devices.data(),
            static_cast<UINT>(devices.size()),
            sizeof(RAWINPUTDEVICE)) == false) {
        std::cout << "Failed to register devices: " << GetLastError()
                  << std::endl;
    }
}

WindowImpl::~WindowImpl()
{
    DestroyWindow(this->handle);
}

void WindowImpl::show()
{
    ShowWindow(this->handle, SW_SHOWDEFAULT);
}

void WindowImpl::minimise()
{
    WINDOWPLACEMENT placement{
        .length = sizeof(WINDOWPLACEMENT),
        .showCmd = SW_MINIMIZE,
    };
    SetWindowPlacement(this->handle, &placement);
}

void WindowImpl::maximise()
{
    WINDOWPLACEMENT placement{
        .length = sizeof(WINDOWPLACEMENT),
        .showCmd = SW_MAXIMIZE,
    };
    SetWindowPlacement(this->handle, &placement);
}

void WindowImpl::restore()
{
    WINDOWPLACEMENT placement{
        .length = sizeof(WINDOWPLACEMENT),
        .showCmd = SW_RESTORE,
    };
    SetWindowPlacement(this->handle, &placement);
}

void WindowImpl::process_events()
{
    MSG msg{};
    while (PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void WindowImpl::set_title(const std::u8string &title)
{
    std::wstring wide_title = utf8_to_wstring(title);
    SetWindowText(this->handle, wide_title.c_str());
}

void WindowImpl::set_cursor_visibility(bool visible)
{
    this->cursor_visible = visible;
    SetCursor(visible ? this->last_cursor : nullptr);
}

Math::UInt2 WindowImpl::get_client_size()
{
    RECT rect{};
    GetClientRect(handle, &rect);
    return Math::UInt2(static_cast<unsigned int>(rect.right),
        static_cast<unsigned int>(rect.bottom));
}

LRESULT WindowImpl::proc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    WindowImpl *window = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT *create = reinterpret_cast<CREATESTRUCT *>(l_param);
        window = reinterpret_cast<WindowImpl *>(create->lpCreateParams);
        SetWindowLongPtr(wnd, GWLP_USERDATA, (LONG_PTR)window);
        window->handle = wnd;
    } else {
        window = reinterpret_cast<WindowImpl *>(
            GetWindowLongPtr(wnd, GWLP_USERDATA));
    }
    if (window != nullptr) {
        return window->handle_message(msg, w_param, l_param);
    } else {
        return DefWindowProc(wnd, msg, w_param, l_param);
    }
}

LRESULT WindowImpl::handle_message(UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) {
        case WM_CLOSE: {
            push_event(Event::WindowClosing{});
            return 0;
        }
        case WM_SIZE: {
            UINT width = LOWORD(l_param);
            UINT height = HIWORD(l_param);
            push_event(Event::WindowResized{
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height),
            });
            return 0;
        }
        case WM_LBUTTONDOWN: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            push_event(
                Event::MouseButtonPressed{Nyx::MouseButton::Left, position});
            return 0;
        }
        case WM_LBUTTONUP: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            push_event(
                Event::MouseButtonReleased{Nyx::MouseButton::Left, position});
            return 0;
        }
        case WM_RBUTTONDOWN: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            push_event(
                Event::MouseButtonPressed{Nyx::MouseButton::Right, position});
            return 0;
        }
        case WM_RBUTTONUP: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            push_event(
                Event::MouseButtonReleased{Nyx::MouseButton::Right, position});
            return 0;
        }
        case WM_MBUTTONDOWN: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            push_event(
                Event::MouseButtonPressed{Nyx::MouseButton::Middle, position});
            return 0;
        }
        case WM_MBUTTONUP: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            push_event(
                Event::MouseButtonReleased{Nyx::MouseButton::Middle, position});
            return 0;
        }
        case WM_XBUTTONDOWN: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            if (GET_XBUTTON_WPARAM(w_param) == XBUTTON1) {
                push_event(
                    Event::MouseButtonPressed{Nyx::MouseButton::X1, position});
            } else {
                push_event(
                    Event::MouseButtonPressed{Nyx::MouseButton::X2, position});
            }
            return TRUE;
        }
        case WM_XBUTTONUP: {
            Math::Int2 position(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
            if (GET_XBUTTON_WPARAM(w_param) == XBUTTON1) {
                push_event(
                    Event::MouseButtonReleased{Nyx::MouseButton::X1, position});
            } else {
                push_event(
                    Event::MouseButtonReleased{Nyx::MouseButton::X2, position});
            }
            return TRUE;
        }
        case WM_MOUSEWHEEL: {
            float delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(w_param)) /
                          WHEEL_DELTA;
            push_event(Event::MouseWheelScrolled{Math::Float2(0.0f, delta)});
            return 0;
        }
        case WM_MOUSEHWHEEL: {
            float delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(w_param)) /
                          WHEEL_DELTA;
            push_event(Event::MouseWheelScrolled{Math::Float2(delta, 0.0f)});
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (!this->cursor_locked) {
                Math::Float2 position(
                    GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
                Math::Float2 delta = position - this->last_mouse_positon;
                push_event(Event::MouseMoved{position, delta});
                this->last_mouse_positon = position;
                return 0;
            }
            break;
        }
        case WM_INPUT: {
            return handle_raw_input(w_param, l_param);
        }
        case WM_SETCURSOR: {
            if (LOWORD(l_param) == HTCLIENT) {
                SetCursor(this->cursor_visible ? this->last_cursor : nullptr);
                return true;
            }
            break;
        }
    }
    return DefWindowProc(this->handle, msg, w_param, l_param);
}

LRESULT WindowImpl::handle_raw_input(WPARAM w_param, LPARAM l_param)
{
    // Get input data
    UINT size = 0;
    GetRawInputData(reinterpret_cast<HRAWINPUT>(l_param), RID_INPUT, nullptr,
        &size, sizeof(RAWINPUTHEADER));
    std::vector<BYTE> raw_input_data(size);
    GetRawInputData(reinterpret_cast<HRAWINPUT>(l_param), RID_INPUT,
        raw_input_data.data(), &size, sizeof(RAWINPUTHEADER));
    RAWINPUT *raw_input = reinterpret_cast<RAWINPUT *>(raw_input_data.data());

    // Process data
    switch (raw_input->header.dwType) {
        case RIM_TYPEKEYBOARD: {
            Nyx::KeyCode key_code =
                translate_key_code(raw_input->data.keyboard.VKey);
            Nyx::ScanCode scan_code =
                translate_scan_code(raw_input->data.keyboard.MakeCode);
            if ((raw_input->data.keyboard.Flags & 1) == RI_KEY_MAKE) {
                push_event(Event::KeyPressed{key_code, scan_code});
            } else {
                push_event(Event::KeyReleased{key_code, scan_code});
            }
            break;
        }
        case RIM_TYPEMOUSE: {
            if (!this->cursor_locked) {
                break;
            }
            // Mouse motion event
            RAWMOUSE &mouse = raw_input->data.mouse;
            if (mouse.usButtonFlags == 0) {
                USHORT flags = mouse.usFlags;
                if (flags & MOUSE_MOVE_ABSOLUTE) {
                    RECT rect{};
                    if (flags & MOUSE_VIRTUAL_DESKTOP) {
                        rect.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
                        rect.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
                        rect.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
                        rect.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
                    } else {
                        rect.left = 0;
                        rect.top = 0;
                        rect.right = GetSystemMetrics(SM_CXSCREEN);
                        rect.bottom = GetSystemMetrics(SM_CYSCREEN);
                    }
                    Math::Float2 absolute(
                        MulDiv(mouse.lLastX, rect.right, 65535) + rect.left,
                        MulDiv(mouse.lLastX, rect.right, 65535) + rect.top);
                    push_event(Event::MouseMoved{Math::Float2::zero,
                        absolute - this->last_mouse_positon});
                    this->last_mouse_positon = absolute;
                } else if (mouse.lLastX != 0 || mouse.lLastY != 0) {
                    push_event(Event::MouseMoved{Math::Float2::zero,
                        Math::Float2(mouse.lLastX, mouse.lLastY)});
                }
            }
            break;
        }
    }
    return 0;
}
}  // namespace Nyx::MSW