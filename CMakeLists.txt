cmake_minimum_required(VERSION 3.7...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    GameB_Linux
    VERSION 0.1
    DESCRIPTION "Linux clone of GameB by Ryan Ries"
    LANGUAGES C
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Ensure we're using -std=c11 instead of -std=gnu11
    set(CMAKE_C_EXTENSIONS OFF)

    # Allow organization of targets into folders
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

add_subdirectory(app)