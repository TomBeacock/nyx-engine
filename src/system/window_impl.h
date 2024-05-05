#pragma once

#include <nyx/events/event.h>

#include <memory>
#include <queue>
#include <string>

namespace Nyx {
class Event;
}

namespace Nyx {
class WindowImpl {
  public:
    virtual ~WindowImpl() = default;

    Event pop_event();
    void push_event(const Event &event);

    virtual void show() = 0;
    virtual void maximise() = 0;
    virtual void minimise() = 0;
    virtual void restore() = 0;
    virtual void process_events() = 0;

    virtual void set_title(const std::u8string &title) = 0;
    virtual void set_cursor_visibility(bool visible) = 0;

  public:
    static std::unique_ptr<WindowImpl> create();

  protected:
    WindowImpl() = default;

  private:
    std::queue<Event> event_queue;
};
}  // namespace Nyx