#include <E3D.h>
#include <E3D/Core/EntryPoint.h>

#include "MenuLayer.h"

class EditorApp : public E3D::Application {
public:
    explicit EditorApp() : Application("Editor", 1280, 720) {
        Push(new MenuLayer());
    }
};

E3D::Application* E3D::CreateApplication(int argc, char** argv) {
    return new EditorApp();
}
