# SDL2-Minesweeper
Learning sdl2
> Refactoring [SDL2-GameDev/Minesweeper](https://github.com/guyllaumedemers/SDL2-GameDev/tree/master/SDL2-Minesweeper)

### TODO - ${PROJECT_NAME}/CMakeLists.txt need to be adapted to Modern CMake practice.
>headers/src files need to be added either with file(GLOB "\*.h" "\*.cpp" )
```
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

# Add includes
target_include_directories(${PROJECT_NAME}
	PUBLIC "${CMAKE_SOURCE_DIR}/external/sdl2/include"
)

# Linking lib
target_link_libraries(${PROJECT_NAME}
	PUBLIC SDL2::SDL2-static
	PUBLIC SDL2::SDL2main
)
```
