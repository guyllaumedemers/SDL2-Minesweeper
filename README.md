# SDL2-Minesweeper
Learning sdl2 and CMake, Out-of-Source Build
> Refactoring [SDL2-GameDev/Minesweeper](https://github.com/guyllaumedemers/SDL2-GameDev/tree/master/SDL2-Minesweeper)

## Quiet Issue // Open Folder Mode only
> #include \<filestream> namespace is not recognized after 'build configuration files' are generated using cmake -G "Visual Studio 17 2022" in RELEASE mode (\*DEBUG mode works fine), even if CXX_STANDARD 17 is specified. Running MSVC 14.3. CMake 3.22. MSVC compiler should be handling properly \<filesystem> header which is part of the STL but isnt. WIll try building and running using mingw-w64 with gcc compiler.

## Visual Studio 17 2022
> Open Folder Mode, Intellisense doesnt update after cmake build config files and compile application [link](https://docs.microsoft.com/en-us/cpp/build/open-folder-projects-cpp?view=msvc-170)

### Testing
> Vanilla project showed that #include \<filestream> is still accessible in release mode when build with CMake using MSVC generator and cl.exe compiler. HOWEVER, once imgui submodule gets added to the project, the same issue arise. sdl2 lib build and works fine without conflicting with #include \<filestream> so I blame imgui cmakelist and will have to investigate on policies version control to fix this conflict.

### Thoughts
> Will have to go over the args list for every prototype functions to verify if it would be better to pass args by lvalue or rvalue</br>
> Keeping const &, rvalue implicitly converted to lvalue when needed.

### ImGui Issue
> Imgui BeginMainMenuBar eats up a part of sdl2 renderer viewport and display 1 tile less than expected.</br>
> *TODO*, retrieve sdl2_context window renderer SDL_Surface* for use in dockable space inside imgui::image() // Otherwise sdl2 context will render on screen and use the whole window context space.

💬 References for patterns are given from : [Large-Scale-Software-Design-John-Lakos](https://www.amazon.ca/Large-Scale-Software-Design-John-Lakos/dp/0201633620)
