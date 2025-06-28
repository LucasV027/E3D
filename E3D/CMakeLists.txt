add_library(E3D STATIC
        src/E3D.h
        src/E3D/Core/EntryPoint.h
        src/E3D/Core/Application.cpp
        src/E3D/Core/Application.h
        src/E3D/Core/Window.cpp
        src/E3D/Core/Window.h
        src/E3D/Core/UI.cpp
        src/E3D/Core/UI.h
        src/E3D/Core/Base.h
        src/E3D/Scene/Scene.h
        src/E3D/Graphics/RenderCommand.cpp
        src/E3D/Graphics/RenderCommand.h
        src/E3D/Event/EventSystem.cpp
        src/E3D/Event/EventSystem.h
)

target_include_directories(E3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(E3D PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

include(Dependencies.cmake)
target_link_libraries(E3D PUBLIC
        glad
        glfw
        glm
        imgui
)
