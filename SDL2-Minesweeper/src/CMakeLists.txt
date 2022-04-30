# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(SRC_FILES Event.cpp GameManager.cpp InputHandler.cpp SDLHandler.cpp Subscriber.cpp)
add_library(src STATIC ${SRC_FILES})
set_target_properties(src PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src")