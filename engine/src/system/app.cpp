#include "nyx/system/app.h"

#include "nyx/assert.h"
#include "nyx/events.h"
#include "nyx/log.h"
#include "nyx/system/window.h"
#include "rendering/renderer.h"

namespace Nyx {
App::App() : window(std::make_unique<Window>())
{
    this->window->show();
}

App::~App() {}

void App::execute()
{
    this->executing = true;
    while (this->executing) {
        while (const auto event = this->window->poll_event()) {
            this->handle_event(event);
        }
        this->window->update();
        this->window->present();
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
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseButtonReleased>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseWheelScrolled>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseMoved>()) {
        return;
    }
}
}  // namespace Nyx