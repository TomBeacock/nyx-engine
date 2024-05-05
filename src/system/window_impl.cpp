#include "window_impl.h"

#include "nyx/events/event.h"

#ifdef NYX_PLATFORM_MSW
#include <platform/msw/window_impl.h>
using WindowImplType = Nyx::MSW::WindowImpl;
#else
#error Unsupported platform
#endif

namespace Nyx {
Event WindowImpl::pop_event()
{
    Event event;
    if (!this->event_queue.empty()) {
        event = this->event_queue.front();
        this->event_queue.pop();
    } else {
        process_events();

        if (!this->event_queue.empty()) {
            event = this->event_queue.front();
            this->event_queue.pop();
        }
    }
    return event;
}

void WindowImpl::push_event(const Event &event)
{
    this->event_queue.push(event);
}

std::unique_ptr<WindowImpl> Nyx::WindowImpl::create()
{
    return std::make_unique<WindowImplType>();
}
}  // namespace Nyx
