#include "nyx/init.h"

#include "nyx/system/app.h"

namespace Nyx {
void launch(int argc, char **argv)
{
    App *app = create_app();
    app->execute();
    delete app;
}
}  // namespace Nyx
