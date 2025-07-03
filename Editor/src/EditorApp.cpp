#include <iostream>

#include <E3D.h>
#include <E3D/Core/EntryPoint.h>

#include "DefaultScene.h"
#include "MeshScene.h"

class EditorApp : public E3D::Application {
public:
    explicit EditorApp(const int scene) : Application("Editor", 1280, 720) {
        std::cout << "Selected scene " << scene << std::endl;
        switch (scene) {
        case 1: SetScene(new MeshScene());
            break;
        default:
            SetScene(new DefaultScene());
        }
    }
};

E3D::Application* E3D::CreateApplication(int argc, char** argv) {
    // atoi returns 0 when it fails
    return new EditorApp(atoi(argv[1]));
}
