#pragma once

#include <memory>

namespace Nyx {
class Event;

class Window {
  public:
    virtual ~Window() = default;

    virtual void show() = 0;
    virtual void maximise() = 0;
    virtual void minimise() = 0;
    virtual bool poll_event(Event &event) = 0;

  public:
    static std::unique_ptr<Window> create();
};
}  // namespace Nyx