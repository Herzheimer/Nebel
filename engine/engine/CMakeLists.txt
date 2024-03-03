project(Engine)

if(Windows11Comp)
    set(platform_engine windows/src/platform.cpp
        ../../libs/glad/src/glad.c)
    set(platform_include windows/include)
endif(Windows11Comp)
if(LinuxComp)
    set(platform_engine linux/src/platform.cpp
        ../../libs/glad/src/glad.c)
    set(platform_include linux/include)
endif(LinuxComp)

add_library(engine STATIC
    ${platform_engine}
    general/src/audio.cpp
    general/src/camera.cpp
    general/src/controller.cpp
    general/src/ecs.cpp
    general/src/game.cpp
    general/src/graphics.cpp
    general/src/importer.cpp
    general/src/input.cpp
    general/src/loader.cpp
    general/src/mesh.cpp
    general/src/renderer.cpp
    general/src/renderer2d.cpp
    general/src/renderer3d.cpp
    general/src/rng.cpp
    general/src/physics2d.cpp
    general/src/scheduler.cpp
    general/src/scripting_system.cpp
    general/src/shader.cpp
    general/src/sprite.cpp
    general/src/texture.cpp
    #general/src/nebel.cpp
    general/src/ui.cpp
)
target_include_directories(engine PUBLIC
    general/include
    ${platform_include}
    ../../libs/glad/include
    ../../libs/SDL-SDL2/include
    #../../libs/freetype/include
    ../../libs/glm/include
    ../../libs/tinygltf-release/include
    ../../libs/MiniAudio
)
if(Windows11Comp)
    target_link_directories(engine PUBLIC
        ../../libs/SDL-SDL2/Release
    )
    target_link_libraries(engine PUBLIC
        SDL2
        #SDL2-static
        #${CMAKE_SOURCE_DIR}/libs/freetype/lib/freetype.lib
    )
endif(Windows11Comp)
if(LinuxComp)
    target_link_directories(engine PUBLIC
        ../../libs/SDL-SDL2/Release
    )
    target_link_libraries(engine PUBLIC
        SDL2
        #SDL2-static
        #${CMAKE_SOURCE_DIR}/libs/freetype/lib/freetype.lib
    )
endif(LinuxComp)
if(Windows11Comp)
    target_compile_definitions(engine PUBLIC TARGET_WINDOWS11)
endif(Windows11Comp)
if(LinuxComp)
    target_compile_definitions(engine PUBLIC TARGET_LINUX)
endif(LinuxComp)
if(AndroidComp)
    target_compile_definitions(engine PUBLIC TARGET_ANDROID)
endif(AndroidComp)
if(WebComp)
    target_compile_definitions(engine PUBLIC TARGET_WEB)
endif(WebComp)