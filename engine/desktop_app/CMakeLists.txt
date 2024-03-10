project(Desktop_App)

set(DeskAppSrc
    src/nebel.cpp
    src/main.cpp
)

add_executable(Desktop_App ${DeskAppSrc})

target_include_directories(Desktop_App PUBLIC
    include
)
target_link_libraries(Desktop_App PRIVATE
    engine
)