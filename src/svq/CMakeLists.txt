set ( SOURCES
	./gfx/utils.cpp
	./gfx/texture.cpp
	./gfx/sprite.cpp
	./gfx/renderable_2d.cpp
	./gfx/renderer_2d.cpp
	./gfx/buffer_layout.cpp
	./gfx/ogl/gl_index_buffer.cpp
	./gfx/ogl/gl_sprite.cpp
	./gfx/ogl/gl_shader.cpp
	./gfx/ogl/gl_program.cpp
	./gfx/ogl/gl_program_manager.cpp
)

# SDL2 libs
find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED)
find_package( SDL2_mixer REQUIRED)
include_directories( sovoq_lib ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

# OpenGL libs
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Boost libs
find_package(Boost COMPONENTS log REQUIRED )
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_LOG_DYN_LINK) # we will use static libs

set (CMAKE_CXX_STANDARD 11)

add_library( sovoq_lib STATIC ${SOURCES} )
 
target_link_libraries( sovoq_lib 
	${SDL2_LIBRARIES} 
	${SDL2_IMAGE_LIBRARIES} 
	${SDL2_MIXER_LIBRARIES} 
	${OPENGL_LIBRARIES} 
	Boost::log
	dl 
)
