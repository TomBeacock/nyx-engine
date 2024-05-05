#include "nyx/system/app.h"

#include "nyx/events.h"
#include "nyx/system/window.h"

#include <iostream>
#include <type_traits>

namespace Nyx {
App::App() : window(std::make_unique<Window>())
{
    this->window->show();
}

void App::execute()
{
    this->executing = true;
    while (this->executing) {
        while (const auto event = this->window->poll_event()) {
            this->handle_event(event);
        }
    }
}

void App::handle_event(const Event &event)
{
    if (event.is<Nyx::Event::WindowClosing>()) {
        this->executing = false;
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::KeyPressed>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::KeyReleased>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseButtonPressed>()) {
        std::cout << data->mouse_button << data->position << std::endl;
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseButtonReleased>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseWheelScrolled>()) {
        std::cout << data->delta << std::endl;
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseMoved>()) {
        std::cout << data->position << ' ' << data->delta << std::endl;
        return;
    }
}
}  // namespace Nyx