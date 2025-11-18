add_library(E3D STATIC
        src/E3D.h

        src/E3D/EntryPoint.h

        src/E3D/Core/Application.cpp
        src/E3D/Core/Application.h
        src/E3D/Core/Window.cpp
        src/E3D/Core/Window.h
        src/E3D/Core/UI.cpp
        src/E3D/Core/UI.h
        src/E3D/Core/Base.h
        src/E3D/Core/Timer.h
        src/E3D/Core/Timer.cpp
        src/E3D/Core/Layer.h
        src/E3D/Core/Layer.cpp
        src/E3D/Core/Event.h
        src/E3D/Core/Event.cpp

        src/E3D/Graphics/RenderCommand.cpp
        src/E3D/Graphics/RenderCommand.h
        src/E3D/Graphics/VertexArray.cpp
        src/E3D/Graphics/VertexArray.h
        src/E3D/Graphics/VertexBufferLayout.h
        src/E3D/Graphics/VertexBufferLayout.cpp
        src/E3D/Graphics/Buffer.h
        src/E3D/Graphics/Buffer.cpp
        src/E3D/Graphics/Program.cpp
        src/E3D/Graphics/Program.h
        src/E3D/Graphics/FrameBuffer.cpp
        src/E3D/Graphics/FrameBuffer.h
        src/E3D/Graphics/Texture.cpp
        src/E3D/Graphics/Texture.h
        src/E3D/Graphics/RenderBuffer.cpp
        src/E3D/Graphics/RenderBuffer.h

        src/E3D/Camera/Camera.h
        src/E3D/Camera/Camera.cpp
        src/E3D/Camera/CameraController.h
        src/E3D/Camera/CameraController.cpp
)

target_include_directories(E3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(vendor)
target_link_libraries(E3D PUBLIC
        glad
        glfw
        glm
        imgui
        objload
        stb
)
