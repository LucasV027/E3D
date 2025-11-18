file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
list(APPEND SOURCES ${HEADERS})

add_library(E3D STATIC ${SOURCES})

target_include_directories(E3D PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(vendor)
target_link_libraries(E3D PUBLIC
        glad
        glfw
        glm
        imgui
        objload
        stb
)
