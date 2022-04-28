# CMakeList.txt : CMake project for SDL2-Minesweeper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Main.cpp")

# Add Include directories to be used by the executable.
target_include_directories(${PROJECT_NAME}
	PUBLIC "${PROJECT_BINARY_DIR}/external/sdl2/include"
)

# Link target directories
target_link_directories(${PROJECT_NAME}
	PUBLIC 	"${PROJECT_BINARY_DIR}/external/sdl2/src"
)

# Link target libraries.
target_link_libraries(${PROJECT_NAME}
	PUBLIC SDL2::SDL2
	PUBLIC SDL2::SDL2main
)