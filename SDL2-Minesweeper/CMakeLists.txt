# CMakeList.txt : CMake project for SDL2-Minesweeper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# retrieve project dependecy at path
file(GLOB_RECURSE SRC_HEADERS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}" *.h *.cpp)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Main.cpp" ${SRC_HEADERS})

target_include_directories(${PROJECT_NAME} 
	PRIVATE "${CMAKE_SOURCE_DIR}/external/sdl2/include"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/sdl_image"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/imgui"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/imgui/backends"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/imgui/misc/single_file"
)

target_link_directories(${PROJECT_NAME} 
	PRIVATE "${CMAKE_SOURCE_DIR}/external/sdl2/src"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/sdl_image"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/imgui"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/imgui/backends"
	PRIVATE "${CMAKE_SOURCE_DIR}/external/imgui/misc/single_file"
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE SDL2
	PRIVATE SDL2main
	PRIVATE SDL2_image
	PRIVATE imgui
	PRIVATE imgui-sdl
	PRIVATE imgui-sdlrenderer
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/res/sprites"
	"${PROJECT_BINARY_DIR}/res/sprites"
)