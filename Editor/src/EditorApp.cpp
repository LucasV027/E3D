#include <E3D.h>
#include <E3D/EntryPoint.h>

#include "DefaultScene.h"

class EditorApp : public E3D::Application {
public:
    EditorApp() : Application("Editor", 1280, 720) {
        SetScene(new DefaultScene());
    }
};

E3D::Application* E3D::CreateApplication(int argc, char** argv) {
    return new EditorApp();
}
