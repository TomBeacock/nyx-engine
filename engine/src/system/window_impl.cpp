#include "window_impl.h"

#include "nyx/events/event.h"

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
}  // namespace Nyx
