#pragma once

#include "Application.h"

extern E3D::Application* E3D::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
    auto app = E3D::CreateApplication(argc, argv);
    app->Run();
    delete app;
}
