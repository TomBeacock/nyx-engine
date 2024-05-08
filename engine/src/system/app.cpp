#include "nyx/system/app.h"

#include "nyx/assert.h"
#include "nyx/events.h"
#include "nyx/log.h"
#include "nyx/system/window.h"
#include "rendering/renderer.h"

namespace Nyx {
App::App()
    : window(std::make_unique<Window>()), renderer(std::make_unique<Renderer>())
{
    this->window->show();
    this->renderer->init(*this->window);
}

App::~App() {}

void App::execute()
{
    this->executing = true;
    while (this->executing) {
        while (const auto event = this->window->poll_event()) {
            this->handle_event(event);
        }
        this->renderer->render();
    }
}

void App::handle_event(const Event &event)
{
    if (event.is<Nyx::Event::WindowClosing>()) {
        this->executing = false;
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::KeyPressed>()) {
        NYX_LOG_F("{}", data->key_code);
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::KeyReleased>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseButtonPressed>()) {
        NYX_LOG_F("{} {}", data->mouse_button, data->position);
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseButtonReleased>()) {
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseWheelScrolled>()) {
        NYX_LOG_F("{}", data->delta);
        return;
    }
    if (const auto data = event.get_if<Nyx::Event::MouseMoved>()) {
        NYX_LOG_F("{} {}", data->position, data->delta);
        return;
    }
}
}  // namespace Nyx