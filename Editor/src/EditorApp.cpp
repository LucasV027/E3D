#include <E3D.h>
#include <E3D/EntryPoint.h>

#include "MenuLayer.h"

inline std::unique_ptr<E3D::Application> CreateApplication(int argc, char** argv) {
    auto app = E3D::CreateScope<E3D::Application>(E3D::Window::Config{
            .title = "[App]",
            .width = 1600,
            .height = 900,
        }
    );
    app->PushLayer<MenuLayer>("MenuLayer");
    return app;
}
