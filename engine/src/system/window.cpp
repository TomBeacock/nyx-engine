#include "nyx/system/window.h"

#include "window_impl.h"

namespace Nyx {
Window::Window() : window_impl(WindowImpl::create()) {}

Window::~Window() {}

void Window::show()
{
    this->window_impl->show();
}

void Window::maximise()
{
    this->window_impl->maximise();
}

void Window::minimise()
{
    this->window_impl->minimise();
}

void Window::restore()
{
    this->window_impl->restore();
}

Event Window::poll_event()
{
    return this->window_impl->pop_event();
}

void Window::set_title(const std::u8string &title)
{
    this->window_impl->set_title(title);
}
void Window::set_cursor_visibility(bool visible)
{
    this->window_impl->set_cursor_visibility(visible);
}
}  // namespace Nyx