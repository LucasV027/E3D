#include <iostream>

#include <E3D.h>
#include <E3D/Core/EntryPoint.h>

#include "DefaultScene.h"
#include "MeshScene.h"

class EditorApp : public E3D::Application {
public:
    explicit EditorApp(const int sceneId) : Application("Editor", 1280, 720) {
        std::cout << "Selected scene: " << sceneId << std::endl;

        switch (sceneId) {
        case 1:
            SetScene(new MeshScene());
            break;
        default:
            SetScene(new DefaultScene());
            break;
        }
    }
};

E3D::Application* E3D::CreateApplication(int argc, char** argv) {
    int sceneId = 0;

    if (argc > 1) {
        try {
            sceneId = std::stoi(argv[1]);
        } catch (const std::exception& e) {
            std::cerr << "Invalid argument: " << argv[1] << ". Falling back to scene 0.\n";
        }
    }

    return new EditorApp(sceneId);
}
