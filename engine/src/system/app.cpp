#include "nyx/system/app.h"

#include "nyx/assert.h"
#include "nyx/events.h"
#include "nyx/log.h"
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
        NYX_LOG("{}", data->key_code);
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::KeyReleased>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseButtonPressed>()) {
        NYX_LOG("{} {}", data->mouse_button, data->position);
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseButtonReleased>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseWheelScrolled>()) {
        NYX_LOG("{}", data->delta);
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseMoved>()) {
        NYX_LOG("{} {}", data->position, data->delta);
        return;
    }
}
}  // namespace Nyx