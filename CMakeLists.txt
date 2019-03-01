CMAKE_MINIMUM_REQUIRED( VERSION 3.5 )

PROJECT( SOVOQ  )

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

SET( CMAKE_INSTALL_PREFIX /opt/game )

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "DEBUG")
  #SET(CMAKE_BUILD_TYPE "RELEASE")
  #SET(CMAKE_BUILD_TYPE "RELWITHDEBINFO")
  #SET(CMAKE_BUILD_TYPE "MINSIZEREL")
ENDIF()

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

if (MSVC)
    ADD_DEFINITIONS(/W3)
elseif (UNIX) #(CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS(-Wall -pedantic)
else ()
    MESSAGE(FATAL_ERROR "CMakeLists.txt has not been tested/written for your compiler.")
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories( 
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/include 
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

add_definitions( -D_GAME_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
add_definitions( -D_SVQ_OPENGL=ON)

add_subdirectory( src/svq ) # sovoq engine library
add_subdirectory( src/sovoqexe ) # standalone sovoq engine executable
#add_subdirectory( src/retrocore ) # libretro core version