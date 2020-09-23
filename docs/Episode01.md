# GameB on Linux

## Episode 1 - Introduction

[Original video link](https://www.youtube.com/watch?v=3zFFrBSdBvA&list=PLlaINRtydtNWuRfd4Ra3KeD6L9FP_tDE7&index=2&t=0s)

Right off the bat, we have our first divergence from Ryan's project: our toolchain. As far as I'm aware, Microsoft has not published a Linux release of Visual Studio or MSVC, so we will have to build a comparable development environment. For reference, I am developing this project on my home desktop machine running Linux Mint 20 with kernel version 5.4.0-48-generic, so I will use `apt` for installing any needed tools and libraries. If you are running another distro, you'll need to translate all the installation commands to whichever package manager is running on your system, e.g. `yum` or `dnf` for Redhat / Fedora / CentOS or `pacman` for Arch / Manjaro.

### Build Tools

The convenient thing about Visual Studio is that it bundles together your code editor / IDE, compiler, and system libraries / headers in a single install step. In Linux, we trade that simplicity for more flexibility in how we write our code and build our programs.

On Linux, the most commonly used compiler for C language programs is, by far, [gcc](https://gcc.gnu.org/). In case this wasn't installed by default, run the following in a terminal to install:

    $ sudo apt install gcc

During the development process, we will likely encounter errors when attempting to run our program, so a debugging tool will definitely be needed.

For Debian / Ubuntu / Mint, there is a handy bundle of packages called `build-essential` that includes a couple of other parts of our toolchain: the GNU C library (libraries and headers for all the C standard libraries we'll need) and `make`, a tool for directing the compilation of all the C files we'll be writing. I'm pretty sure a similar bundle exists for other distros, but it will likely have a slightly different name.

    $ sudo apt install build-essential

Finally, I'll also be using the `cmake` build system, mainly due to its ubiquity but also due to the fact that I am still very much a `cmake` noob and can use the practice. I'll refer heavily to [this guide](https://cliutils.gitlab.io/modern-cmake/) as well as the official documentation when it comes to writing the various CMakeLists.txt files that will be needed to build our project.

    $ sudo apt install cmake

At this point, I have `gcc` version 9.3.0 and `cmake` version 3.16.3 installed on my system.

### Code Editor

There are many options available for creating and editing code files on Linux, ranging from the older terminal based editors like vim or Emacs to newer desktop apps like Atom or Sublime. My editor of choice is [Visual Studio Code](https://code.visualstudio.com/), and I use a couple of handy extensions to make life easier.

- [C/C++ ](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools): IntelliSense, debugging, and code browsing for C and C++
- [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake): CMake language support for writing all the CMakeLists.txt files we'll need
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools): Build our project and run from within Visual Studio Code

Of these, I would highly recommend the CMake Tools extension at a minimum as it will allow us to most closely replicate the build process Ryan demonstrates in his videos. You can refer to the [official tutorial](https://code.visualstudio.com/docs/cpp/cmake-linux) to see how you can set up and use the extension for this project.

### First Code and Build

The following is the first bit of C code that is compiled in the video.

    int main()
    {
        return 0;
    }

Since we don't have Visual Studio to automatically compile and link all of our code, we'll use `cmake` to manage the build process. The CMakeLists.txt file in the project root folder defines the project, sets a couple of useful compilation flags, and adds a link to the subdirectory where we'll store our program's source code. For now, that will just be the `app` directory, but we will add other directories later as we progress through the project. In the `app` directory, there is the main.c file containing the minimal C code snippet above and another CMakeLists.txt directing the build of our program executable named `GameB`. The project could then be built in a terminal using the following commands (assuming you've navigated to the root directory of the project):

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

This set of commands will create a `build` directory within the project, use the hierarch of CMakeLists.txt files to generate the appropriate makefiles, and finally compile the project. Within the `build` directory, a new directory name `app` will be created to house the executable file for the program. Alternatively, the CMake Tools extension in Visual Studio Code allows you to perform these steps inside your editor instead of typing commands into a terminal. Within Visual Studio Code, open the command palette (using either Ctrl-Shift-P or the View menu) and enter `CMake:Configure`. The first time you do this, you might be asked to choose which compiler you want CMake to use. In my case, I selected `gcc 9.3.0`. This will essentially perform the first 3 commands above, i.e. creating the build directory and running cmake to create the project makefiles. You can then press F7 to build the project (equivalent to issuing the `make` command above). Doing these steps will likely cause a terminal to appear inside Visual Studio Code; if not, you can use the Terminal menu to show a new terminal. In the terminal, navigate to the `build/app` directory and run the new executable. At this point, nothing should happen since the C code does nothing but immediately return.

### ASCII vs Unicode

We will also make the choice to stick with the ASCII character set throughout the project as Ryan has done. However, his demonstration of the difference between ASCII and Unicode strings via the `OutputDebugStringA` and `OutputDebugStringW` functions will not directly translate to Linux for a couple of reasons. First of all, these functions are both part of the Win32 API included with `windows.h`, which is not available or useable in Linux. Also, the system debugger output which these functions write to does not exist in Linux. I have instead put together a similar example illustrating the difference using standard library functions. It should be noted that mixing calls to printf and wprintf in a single program results in [undefined behavior per the C standard](https://stackoverflow.com/a/8682010), so that is why the calls are wrapped inside the switch block.

    #include <stdio.h>
    #include <wchar.h>
    #include <ctype.h>
 
    int main(int argc, char* argv[])
    {
        if (argc == 2) {
            switch (toupper(argv[1][0])) {
                case 'A': {
                    printf("Hello from ASCII Land!\n");
                    break;
                }
                    case 'U': {
                    wprintf(L"Hello from Unicode Land!\n");
                    break;
                }
                default: {
                    printf("Error: use \'GameB a\' or \'GameB u\'.\n");
                    break;
                }
            }
        } else {
            printf("Error: use \'GameB a\' or \'GameB u\'.\n");
        }

        return 0;
    }

Running the program with either parameter provided should print the appropriate output string.

    $ ./GameB a
    Hello from ASCII Land!
    $ ./GameB u
    Hello from Unicode Land!

***

[Table of Contents](../README.md) | [Next](Episode02.md)