project ( sovoq_exe )

set ( SOURCES
    ./sovoq.cpp
)

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED)
find_package( SDL2_mixer REQUIRED)
include_directories( sovoq ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

set (CMAKE_CXX_STANDARD 11)

add_executable ( sovoq ${SOURCES} )

set_target_properties( sovoq PROPERTIES OUTPUT_NAME "game" )
 
target_link_libraries( 
	sovoq 
	sovoq_lib
	${SDL2_LIBRARIES} 
	${SDL2_IMAGE_LIBRARIES} 
	${SDL2_MIXER_LIBRARIES} 
	${OPENGL_LIBRARIES} 
)
