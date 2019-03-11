set ( SOURCES
	./app.cpp
	#./gfx/utils.cpp
	./gfx/index_buffer.cpp
	./gfx/vertex_buffer.cpp
	./gfx/frame_buffer.cpp
	./gfx/vertex_array.cpp
	./gfx/texture.cpp
	./gfx/renderable_2d.cpp
	./gfx/sprite.cpp
	./gfx/shader.cpp
	./gfx/renderer_2d.cpp
	./gfx/buffer_layout.cpp
	# OpenGL
	./gfx/ogl/gl_common.cpp
	./gfx/ogl/gl_texture.cpp
	./gfx/ogl/gl_vertex_buffer.cpp
	./gfx/ogl/gl_index_buffer.cpp
	./gfx/ogl/gl_frame_buffer.cpp
	./gfx/ogl/gl_vertex_array.cpp
	./gfx/ogl/gl_shader.cpp
)

# GLEW libs
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

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
	${GLEW_LIBRARIES}
	Boost::log
	dl 
)
