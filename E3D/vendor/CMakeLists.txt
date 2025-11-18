include(FetchContent)

find_package(OpenGL REQUIRED)

add_subdirectory(glad)
add_subdirectory(GLFW)
add_subdirectory(ImGui)
add_subdirectory(glm)
add_subdirectory(stb)
add_subdirectory(objload)


