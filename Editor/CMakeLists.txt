add_executable(EditorApp src/EditorApp.cpp)

target_include_directories(EditorApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../E3D/src)

target_link_libraries(EditorApp PRIVATE E3D)
