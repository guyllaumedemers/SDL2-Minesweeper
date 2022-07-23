# SDL2-Minesweeper
Learning sdl2 and CMake, Out-of-Source Build
> Refactoring [SDL2-GameDev/Minesweeper](https://github.com/guyllaumedemers/SDL2-GameDev/tree/master/SDL2-Minesweeper)

## Overview
> SDL2-Minesweeper is a Template project allowing usage of various Graphic APIs lib for Rendering. InDEV...

### ImGui Issue
> ImGuiContext* throw exception callback upon calling ImGui::GetCurrentWindow(). HOW To Reproduce: Run the application executable and Select either **New Game**, or **Any difficulty** from the menu dropdown.</br>
``Exception thrown: write access violation. g.**CurrentWindow** was nullptr.``

## Quiet Issue // Open Folder Mode only
> #include \<filestream> namespace is not recognized after 'build configuration files' are generated using cmake -G "Visual Studio 17 2022" in RELEASE mode (\*DEBUG mode works fine), even if CXX_STANDARD 17 is specified. Running MSVC 14.3. CMake 3.22. MSVC compiler should be handling properly \<filesystem> header which is part of the STL but isnt. WIll try building and running using mingw-w64 with gcc compiler.

💬 References for patterns and physical desing are given from : [Design Patterns: Elements of Reusable Object‑Oriented Software](https://www.amazon.ca/-/fr/Gamma-Erich-ebook/dp/B000SEIBB8), [Large-Scale-Software-Design-John-Lakos](https://www.amazon.ca/Large-Scale-Software-Design-John-Lakos/dp/0201633620)
