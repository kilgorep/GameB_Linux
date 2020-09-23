add_executable(GameB main.c)
target_compile_features(GameB PRIVATE c_std_11)
target_compile_options(GameB PRIVATE -Wpedantic
                                     -pedantic-errors
                                     -Werror
                                     -Wall
                                     -Wextra
                                     -Waggregate-return
                                     -Wbad-function-cast
                                     -Wcast-align
                                     -Wcast-qual
                                     -Wfloat-equal
                                     -Wformat=2
                                     -Wlogical-op
                                     -Wmissing-declarations
                                     -Wmissing-include-dirs
                                     -Wmissing-prototypes
                                     -Wnested-externs
                                     -Wpointer-arith
                                     -Wredundant-decls
                                     -Wsequence-point
                                     -Wshadow
                                     -Wstrict-prototypes
                                     -Wswitch
                                     -Wundef
                                     -Wunreachable-code
                                     -Wunused-but-set-parameter
                                     -Wwrite-strings)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(GameB ${SDL2_LIBRARIES})

# TODO: add links to the various libraries we'll eventually be writing
# target_link_libraries(app PRIVATE library_target_01)