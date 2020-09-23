# GameB on Linux

## Episode 2 - Win32 Basics

[Original video link](https://www.youtube.com/watch?v=lw1TT0W0IYo&list=PLlaINRtydtNWuRfd4Ra3KeD6L9FP_tDE7&index=2)

### Compiler Warnings

The video starts with some good discussion of how to go about setting warning levels and other flags for the compiler within Visual Studio. For this project however, we'll need to set these within our CMakeLists.txt files. There are [a couple of ways we can go about this](https://foonathan.net/2018/10/cmake-warnings/): adding them to the global `CMAKE_C_FLAGS` variable to affect all targets, or using `target_compile_options` with each target definition to allow customization of flags per target. I'll go with the suggested course in the linked article and choose the latter course of action. As for what flags to set, I'll refer to an [excellent post in the C_Programming subreddit](https://www.reddit.com/r/C_Programming/comments/ievcev/what_is_the_most_effective_set_of_gcc_warning/g2jrvgk/) for a fairly rigorous set of compiler warnings to include.

### So About Win32...

In Linux, the Win32 API is not available for programmers to use in the programs, so we must find some way to access equivalent functionality at a roughly similar level of abstraction. Early on, we are mainly concerned with creating a window for the game, but later we will want to add things like graphics rendering, sound, and gamepad input handling. Fortunately there is a library called [SDL](https://www.libsdl.org/) which can manage these needs for us. To install the library, simply issue the following command in a terminal:

    $ sudo apt install libsdl2-dev libsdl2-2.0-0

Once we've installed the library, we'll need to let the compiler know we plan to use the functions it defines in our project. This will simply consist of adding the appropriate library linkage statements to our CMakeLists.txt files. In the root CMakeLists.txt, we add a requirement for SDL2 to be installed on the target system.

    find_package(SDL2 REQUIRED)

In app/CMakeLists.txt, we add statements to point to the appropriate include directories and link SDL to the main executable.

    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(GameB ${SDL2_LIBRARIES})

While the program entry point function under Win32 is the `WinMain` function that Ryan discusses, we can stick with regular old `main` for a SDL app on Linux. To verify that everything was set up correctly, I pasted the following code into the app/main.c file (credit to [Trenki's Dev Blog](https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/)):

    #include "SDL.h"
 
    int main(int argc, char* argv[])
    {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Window* window  = SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0
        );

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(3000);

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }

When I first tried to build the program, I had a couple of errors pop up in the build output. The first of these dealt with having the `argc` and `argv[]` arguments in the declaration of `main` but not using them inside the function. This is raised thanks to the -Wunused-parameter flag included when we specifed the -Wall and -Wextra compiler flags. There are a couple of ways to fix this particular error: either replace the parameter list with `void` or add the `__attribute__((unused))` attribute in front of both parameters. I tried both approaches with my own testing with success in both cases. The second method is a better analogue to Ryan's use of the `UNREFERENCED_PARAMETER` macro in the video when suppressing the warnings that popped up when he tried to build his first version of `WinMain`.

The other error I saw was related to the flag -Wdeclaration-after-statement which was raised by the declarations of `window` and `renderer` after having called `SDL_Init`. In the old C89 standard, programmers were forced to declare all variables that would be used in a function at the top of the function definition before any other code. Starting with C99, this restriction was eliminated, allowing variables to be declared at any point in the function. Since I've decided to use the C11 standard for this project and want all of its benefits, I've gone ahead and removed the -Wdeclaration-after-statement flag from the compiler flags list in app/CmakeLists.txt.

With these changes made, the code compiles without error and runs as expected. To briefly explain what the code does, the call to `SDL_Init` initializes the SDL library for the program's use. We then create a window with a size of 640 by 480 pixels and define a renderer that will paint the window black. The window is then displayed for 3000 milliseconds before being destroyed and the program exiting.

***

[Previous](Episode01.md) | [Table of Contents](../README.md) | Next