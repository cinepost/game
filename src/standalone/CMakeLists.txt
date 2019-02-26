project ( soVoq )

set ( SOURCES
    ./game.cpp
    ./sprites/sprite.cpp
    ./ogl/shader.cpp
    ./ogl/program.cpp
    ./ogl/program_manager.cpp
)
include_directories( 
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/src/ogl
	${PROJECT_SOURCE_DIR}/src/sprites
)

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED)
find_package( SDL2_mixer REQUIRED)
include_directories( standalone ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

set (CMAKE_CXX_STANDARD 11)

add_executable ( standalone ${SOURCES} )

set_target_properties( standalone PROPERTIES OUTPUT_NAME "game" )
 
target_link_libraries( standalone ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${OPENGL_LIBRARIES} )
