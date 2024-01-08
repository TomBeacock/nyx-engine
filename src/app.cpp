#include "nyx/app.h"

#include "nyx/event.h"
#include "nyx/window.h"

Nyx::App::App() : window(Nyx::Window::create())
{
    this->window->show();
}

Nyx::App::~App() {}

void Nyx::App::execute()
{
    this->executing = true;
    while (this->executing) {
        Event e;
        while (this->window->poll_event(e)) {
            if (e.get_type() == Event::Close) {
                this->executing = false;
            }
        }
    }
}