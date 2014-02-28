cmake_minimum_required(VERSION 2.6)

set(PRJ_NAME "tetris")
project(${PRJ_NAME})

# There are lots of scripts with cmake for finding external libraries. 
# see /usr/share/cmake-2.8/Modules/Find*.cmake for more examples
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenGL REQUIRED)

option(USE_GLUT "Use glut instead of SDL" true)
if(USE_GLUT)
	message("use libGLUT")
	find_package(GLUT REQUIRED)
	add_definitions(-DUSE_GLUT)
else()
	message("use libSDL2")
	find_package(SDL2 REQUIRED)
	remove_definitions(-DUSE_GLUT)
endif()

set(CMAKE_C_FLAGS "-g -Wall -std=c99")
set(CMAKE_CXX_FLAGS "-g -Wall ") # -std=c++11

# make assertions do nothing if macro NDEBUG is defined
add_definitions(-DNDEBUG) 

set(TETRIS_SRC
	src/Engine.cpp
	src/Grid.cpp
	src/main.cpp
	src/Tetromino.cpp
)

set(TETRIS_HDR
	src/Engine.h
	src/Grid.h
	src/Tetromino.h
)

add_executable(${PRJ_NAME} ${TETRIS_SRC} ${TETRIS_HDR})

target_link_libraries(${PRJ_NAME} ${OPENGL_LIBRARY} )

if(USE_GLUT)
	target_link_libraries(${PRJ_NAME} ${GLUT_LIBRARY})
else()
	target_link_libraries(${PRJ_NAME} ${SDL2_LIBRARY})
endif()
