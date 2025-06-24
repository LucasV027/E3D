add_library(E3D STATIC
        src/E3D.h)

target_sources(E3D PRIVATE
        src/E3D/EntryPoint.h
        src/E3D/Application.cpp
        src/E3D/Application.h
        src/E3D/Window.cpp
        src/E3D/Window.h
        src/E3D/UI.cpp
        src/E3D/UI.h
        src/E3D/Base.h
        src/E3D/Scene.h
        src/E3D/DefaultScene.cpp
        src/E3D/DefaultScene.h
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
