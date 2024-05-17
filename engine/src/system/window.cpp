#include "nyx/system/window.h"

#include "nyx/events.h"
#include "rendering/renderer.h"

#ifdef NYX_PLATFORM_MSW
    #include "system/msw/window_impl.h"
using WindowImplType = Nyx::MSW::WindowImpl;
#else
    #error Unsupported platform
#endif

namespace Nyx {
Window::Window()
    : window_impl(std::make_unique<WindowImplType>()),
      renderer(std::make_unique<Renderer>()),
      width(0),
      height(0)
{
    this->renderer->init(*this);
}

Window::~Window() {}

void Window::update()
{
    this->renderer->update();
}

void Window::present()
{
    this->renderer->render();
}

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
    Event event = this->window_impl->pop_event();
    filter_event(event);
    return event;
}

void Window::set_title(const std::u8string &title)
{
    this->window_impl->set_title(title);
}

void Window::set_cursor_visibility(bool visible)
{
    this->window_impl->set_cursor_visibility(visible);
}

uint32_t Window::get_client_width() const
{
    return this->window_impl->get_client_size().x;
}

uint32_t Window::get_client_height() const
{
    return this->window_impl->get_client_size().y;
}

const WindowImpl &Window::get_impl() const
{
    return *this->window_impl;
}

void Window::filter_event(const Event &event)
{
    if (const auto data = event.get_if<Event::WindowResized>()) {
        this->width = data->width;
        this->height = data->height;
        this->renderer->resize(this->width, this->height);
    }
}
}  // namespace Nyx