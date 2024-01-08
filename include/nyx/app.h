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

class App {
  public:
    App();
    ~App();

    void execute();

  private:
    bool executing = false;
    std::unique_ptr<Window> window;
};
}  // namespace Nyx

extern Nyx::App *create_app();