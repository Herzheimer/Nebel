project(App)

set(AppSrc
    src/nebel.cpp
    src/main.cpp
)

add_executable(app ${AppSrc})

target_include_directories(app PUBLIC
    include
)
target_link_libraries(app PRIVATE
    engine
)