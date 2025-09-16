cmake_minimum_required (VERSION 3.22)

set (PROJECT GSoft)

# set project name
project (${PROJECT})

# include necessary submodules
list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
)

#set the default path for output
#set(EXECUTABLE_OUTPUT_PATH ${radar_SOURCE_DIR}/build)
#set(LIBRARY_OUTPUT_PATH ${radar_SOURCE_DIR}/build)

# TinyXML
#find_package(TinyXML REQUIRED)

# OpenCV
#find_package(OpenCV REQUIRED )

include(FindFreetype)
include_directories(${FREETYPE_INCLUDE_DIRS})

# boost
#set(Boost_USE_STATIC_LIBS        OFF) # only find static libs
#set(Boost_USE_MULTITHREADED      ON)
##set(Boost_USE_STATIC_RUNTIME    OFF)

#find_package(Boost 1.54.0 COMPONENTS lexical_cast property_tree date_time log filesystem system)

# pkg-config
include (FindPkgConfig)

# gl
pkg_check_modules (GLEW glew)

find_package(GLFW3 REQUIRED)

#message(STATUS "opencv: ${OpenCV_LIBS}")

#message(STATUS "gtk GLFW: ${GLFW_INCLUDE_DIRS}")
#message(STATUS "gtk GLFW: ${GLFW_LIBRARIES}")

#message(STATUS "gtk GLEW: ${GLEW_INCLUDE_DIRS}")
#message(STATUS "gtk GLEW: ${GLEW_LIBRARIES}")

add_definitions(-c -pipe -O0 -g -Wall)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
#include_directories(${TINYXML_INCLUDE_DIRS})

#if(Boost_FOUND)
#   	include_directories(${Boost_INCLUDE_DIRS})
#endif()

# set search include path
include_directories(".")


# The project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

# build

add_definitions(-std=c++11)

set (HEADERS
./shader.h
./texture.h
./font.h
./buffer.h
./resource_manager.h
./render.h
./node.h
./camera.h
./popup_menu.h
./widget.h
./ui.h
)


set (SOURCES
./shader.cpp
./texture.cpp
./font.cpp
./buffer.cpp
./resource_manager.cpp
./render.cpp
./node.cpp
./camera.cpp
./popup_menu.cpp
./widget.cpp
./ui.cpp
)

#add_library(gsoft SHARED ${SOURCES})

#add_executable (test-camera test-camera.cpp ${SOURCES})
#target_link_libraries (test-camera ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} freeimage freetype SOIL)

add_executable (test-node test-node.cpp) #${SOURCES})
target_link_libraries (test-node ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} shade freeimage freetype SOIL)

#add_executable (test-widgets test-widgets.cpp )
#target_link_libraries (test-widgets ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} gsoft freeimage freetype)


#add_executable (test-line-strip test-line-strip.cpp ${SOURCES})
#target_link_libraries (test-line-strip ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} freeimage)

#add_executable (test-quad test-quad.cpp ${SOURCES})
#target_link_libraries (test-quad ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} freeimage)



#add_executable (${PROJECT} ${SOURCES})
#target_link_libraries (${PROJECT} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} freeimage freetype)


add_custom_target(clean-all
    COMMAND rm -f Makefile
    COMMAND rm -f cmake_install.cmake
    COMMAND rm -f install_manifest.txt
    COMMAND rm -f CMakeCache.txt
    COMMAND rm -R -f CMakeFiles
)

# add_custom_target(install-all
#     COMMAND cp ./libgsoft.so /usr/lib/
# )

