# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Project Setup
project ("SDL2-Minesweeper")
set(VERSION 0.1)
set(PROJECT_DESCRIPTION "Minesweeper -- Project 2022 -- ImGUI -- SDL2")
set(LANGUAGE C CXX)

# Set Project C++ Standard used.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILE_FEATURES cxx_std_17)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

# Update Git submodule, updated version to point to top level cmakelists
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# imgui doesnt have a cmakelists in his submodule by default, gist version -> https://gist.github.com/rokups/f771217b2d530d170db5cb1e08e9a8f4
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/external/sdl2/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
elseif(NOT EXISTS "${CMAKE_SOURCE_DIR}/external/sdl_image/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# Add subdirectory to add other cmakelists
add_subdirectory("${CMAKE_SOURCE_DIR}/${PROJECT_NAME}")
add_subdirectory("${CMAKE_SOURCE_DIR}/external/sdl2")
add_subdirectory("${CMAKE_SOURCE_DIR}/external/sdl_image")
add_subdirectory("${CMAKE_SOURCE_DIR}/external/imgui")