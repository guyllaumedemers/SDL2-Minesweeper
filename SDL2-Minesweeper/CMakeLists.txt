# CMakeList.txt : CMake project for SDL2-Minesweeper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# setting project dependecy path
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}")

# Adding all project local dependencies
list(APPEND SOURCE_FILES
	"${SOURCE_DIR}/headers/EventHandler.h"
	"${SOURCE_DIR}/src/EventHandler.cpp"
	"${SOURCE_DIR}/headers/GameManager.h"
	"${SOURCE_DIR}/src/GameManager.cpp"
	"${SOURCE_DIR}/headers/InputHandler.h"
	"${SOURCE_DIR}/src/InputHandler.cpp"
	"${SOURCE_DIR}/headers/SDLHandler.h"
	"${SOURCE_DIR}/src/SDLHandler.cpp"
	"${SOURCE_DIR}/headers/Subscriber.h"
	"${SOURCE_DIR}/src/Subscriber.cpp"
)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Main.cpp" ${SOURCE_FILES})

# Specifies include directories to use when compiling a given target. 
target_include_directories(${PROJECT_NAME} 
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/sdl2/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/backends"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/misc/cpp"
)

# Specifies the paths in which the linker should search for libraries when linking a given target.
target_link_directories(${PROJECT_NAME} 
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/sdl2/src"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/backends"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/misc/cpp"
)

# Specify libraries or flags to use when linking a given target and/or its dependents.
target_link_libraries(${PROJECT_NAME}
	PUBLIC SDL2::SDL2main
	PUBLIC SDL2::SDL2-static
	PUBLIC imgui
)