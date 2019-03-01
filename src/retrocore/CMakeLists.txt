project(retrocore)

# SDL2 libs
find_package( SDL2 REQUIRED )

include_directories( sovoq_lib ${SDL2_INCLUDE_DIRS} )

set (CMAKE_CXX_STANDARD 11)

add_library(retrocore SHARED
    libretro.h
    libretro_interface.cpp
)

target_link_libraries( 
	retrocore 
	sovoq_lib
	#${SDL2_LIBRARIES}  
)

