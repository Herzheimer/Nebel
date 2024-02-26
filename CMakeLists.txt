cmake_minimum_required(VERSION 3.5)
project(GameEngine)
set (CMAKE_CXX_STANDARD 17)

option(Windows11Comp "Windows 11" ON)
option(LinuxComp "Linux" OFF)
option(AndroidComp "Android" OFF)
option(WebComp "WEB" OFF)

option(OPENGL_GFX "Opengl" ON)

add_subdirectory(engine/engine)
add_subdirectory(engine/app)