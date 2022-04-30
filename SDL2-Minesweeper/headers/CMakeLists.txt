# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(HEADER_FILES Event.h GameManager.h InputHandler.h SDLHandler.h Subscriber.h)
add_library(headers STATIC ${HEADER_FILES})
set_target_properties(headers PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(headers PUBLIC "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/headers")