#pragma once

#include <memory>
#include <string>

namespace Nyx {
class Event;

class Window {
  public:
    virtual ~Window() = default;

    virtual void show() = 0;
    virtual void maximise() = 0;
    virtual void minimise() = 0;
    virtual void restore() = 0;
    virtual bool poll_event(Event &event) = 0;

    virtual void set_title(const std::u8string &title) = 0;

  public:
    static std::unique_ptr<Window> create();
};
}  // namespace Nyx