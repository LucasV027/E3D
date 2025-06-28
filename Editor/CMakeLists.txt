add_executable(EditorApp
        src/EditorApp.cpp
        src/DefaultScene.cpp
        src/DefaultScene.h
)

target_include_directories(EditorApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../E3D/src)

target_compile_definitions(EditorApp PRIVATE ASSETS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/assets/\")

target_link_libraries(EditorApp PRIVATE E3D)
