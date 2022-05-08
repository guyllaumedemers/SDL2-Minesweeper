# CMakeList.txt : CMake project for SDL2-Minesweeper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# retrieve project dependecy at path
file(GLOB_RECURSE SRC_HEADERS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}" *.h *.cpp)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Main.cpp" ${SRC_HEADERS})

target_include_directories(${PROJECT_NAME} 
	PUBLIC "${CMAKE_SOURCE_DIR}/external/sdl2/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/sdl_image"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/backends"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/misc/cpp"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/misc/single_file"
)

target_sources(${PROJECT_NAME} 
	PUBLIC "${CMAKE_SOURCE_DIR}/external/sdl2/src"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/sdl_image"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/backends"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/misc/cpp"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/imgui/misc/single_file"
)

#target_link_directories(${PROJECT_NAME} 
#	PUBLIC "${CMAKE_SOURCE_DIR}/external/sdl2"
#)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC SDL2-static
	PUBLIC SDL2main
	PUBLIC SDL2_image
	PRIVATE imgui
	PRIVATE imgui-sdl
	PRIVATE imgui-sdlrenderer
	PRIVATE imgui-stdlib
)