project(App)

set(AppSrc
    src/main.cpp
)

add_executable(app ${AppSrc})

target_include_directories(app PUBLIC
    include
)
target_link_libraries(app PRIVATE
    engine
)