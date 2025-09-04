add_executable(EditorApp
        src/EditorApp.cpp
        src/BaseLayer.cpp
        src/BaseLayer.h
        src/MenuLayer.cpp
        src/MenuLayer.h
)

target_include_directories(EditorApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../E3D/src)

target_compile_definitions(EditorApp PRIVATE ASSETS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/assets/\")

target_link_libraries(EditorApp PRIVATE E3D)
