#include <E3D.h>
#include <E3D/EntryPoint.h>

class EditorApp : public E3D::Application {};

E3D::Application* E3D::CreateApplication(int argc, char** argv) {
    return new EditorApp();
}
