#pragma once

#include <memory>

#define NYX_LAUNCH_APP(app)                                                    \
    NYX_IMPLEMENT_MAIN                                                         \
    NYX_IMPLEMENT_APP(app)

#define NYX_IMPLEMENT_MAIN                                                     \
    int main(int argc, char **argv)                                            \
    {                                                                          \
        Nyx::launch(argc, argv);                                               \
    }

#define NYX_IMPLEMENT_APP(app)                                                 \
    Nyx::App *create_app()                                                     \
    {                                                                          \
        return new app;                                                        \
    }

namespace Nyx {
class Window;
class Renderer;
class Event;
}  // namespace Nyx

namespace Nyx {

class App {
  public:
    App(const App &) = delete;
    App(const App &&) = delete;
    virtual ~App();

    void execute();

    Window &get_window() { return *this->window; }

    App &operator=(const App &) = delete;
    App &operator=(const App &&) = delete;

  protected:
    App();

  private:
    void handle_event(const Event &e);

  private:
    bool executing = false;
    std::unique_ptr<Window> window;
};
}  // namespace Nyx

extern Nyx::App *create_app();