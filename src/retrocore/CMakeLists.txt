project(RetroTutorial1)

set (CMAKE_CXX_STANDARD 11)

add_library(${PROJECT_NAME} SHARED
    libretro.h
    libretro_interface.cpp
)

