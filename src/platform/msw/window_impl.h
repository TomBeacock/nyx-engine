#pragma once

#include "msw.h"
#include "nyx/math.h"
#include "system/window_impl.h"

#include <string>

namespace Nyx {
class Event;
}

namespace Nyx::MSW {
class WindowImpl : public Nyx::WindowImpl {
  public:
    WindowImpl();
    virtual ~WindowImpl() override;

    virtual void show() override;
    virtual void minimise() override;
    virtual void maximise() override;
    virtual void restore() override;
    virtual void process_events() override;

    virtual void set_title(const std::u8string &title) override;
    virtual void set_cursor_visibility(bool visible) override;

  public:
    static LRESULT proc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param);

  private:
    LRESULT handle_message(UINT msg, WPARAM w_param, LPARAM l_param);
    LRESULT handle_raw_input(WPARAM w_param, LPARAM l_param);

  private:
    HWND handle = nullptr;
    Math::Float2 last_mouse_positon = Math::Float2::zero;
    HCURSOR last_cursor = nullptr;
    bool cursor_visible = true;
    bool cursor_locked = false;
};
}  // namespace Nyx::MSW