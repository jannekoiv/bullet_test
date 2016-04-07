cmake_minimum_required(VERSION 3.5)
project(bullet_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_FILES src/main.cpp src/Box.cpp include/Box.h src/Camera.cpp include/Camera.h)
add_executable(bullet_test ${SOURCE_FILES})

INCLUDE(FindPkgConfig)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindGLEW REQUIRED)
INCLUDE(FindBullet REQUIRED)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(bullet_test ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${BULLET_LIBRARIES})
