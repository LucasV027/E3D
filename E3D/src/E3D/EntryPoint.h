#pragma once

#include "Core/Application.h"

extern std::unique_ptr<E3D::Application> CreateApplication(int argc, char** argv);

int main(const int argc, char** argv) {
    const auto app = CreateApplication(argc, argv);
    app->Run();
}
