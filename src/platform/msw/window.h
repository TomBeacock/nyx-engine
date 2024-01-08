#pragma once

#include "msw.h"
#include "nyx/window.h"

namespace Nyx {
class Event;
}

namespace Nyx::MSW {
class Window : public Nyx::Window {
  public:
    Window();
    virtual ~Window();

    virtual void show() override;
    virtual void minimise() override;
    virtual void maximise() override;
    virtual bool poll_event(Event &event) override;

  private:
    LRESULT handle_message(UINT msg, WPARAM w_param, LPARAM l_param);

  public:
    static LRESULT proc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param);

  private:
    HWND handle = nullptr;
    Event *event = nullptr;
};
}  // namespace Nyx::MSW