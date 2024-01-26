#include <nyx/nyx.h>

class HelloWorldApp : public Nyx::App {
  public:
    HelloWorldApp();
};

HelloWorldApp::HelloWorldApp()
{
    Nyx::Window &window = get_window();
    window.set_title(u8"Hello World");
}

NYX_LAUNCH_APP(HelloWorldApp)