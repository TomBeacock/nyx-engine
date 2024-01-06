#pragma once

#define NYX_LAUNCH_APP(app)                                                    \
    NYX_IMPLEMENT_MAIN                                                         \
    NYX_IMPLEMENT_APP(app)

#define NYX_IMPLEMENT_MAIN                                                     \
    int main(int argc, char **argv)                                            \
    {                                                                          \
        Nyx::launch(argc, argv);                                               \
    }

#define NYX_IMPLEMENT_APP(app)                                                 \
    static Nyx::App *create_app()                                              \
    {                                                                          \
        return new app;                                                        \
    }

namespace Nyx {
class App {};
}  // namespace Nyx

extern Nyx::App *create_app();