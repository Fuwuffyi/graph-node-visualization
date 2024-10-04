cmake_minimum_required(VERSION 3.29)
project(grapher)

# Compiler options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wshadow -Wold-style-cast -Wcast-align -Wformat=2 -Wconversion -Wunreachable-code -Wno-unused-parameter -Wno-unused-variable -Waddress -Wdangling-pointer -Wformat-nonliteral -Wnoexcept -Wctor-dtor-privacy -Wenum-compare -Wsign-compare -Wswitch -Wnoexcept-type -Wno-overloaded-virtual -Wcast-qual -Wcomment -Woverloaded-virtual -Wreorder -Warray-bounds -Wchar-subscripts -Wconversion-null -Wdeprecated -Wfloat-equal -Winit-self -Wlogical-op -Wmissing-braces -Wmissing-field-initializers -Wmissing-include-dirs -Wno-narrowing -Wredundant-decls -Wsign-conversion -Wswitch-default -Wundef -Wunused-but-set-variable -Wunused-function -Wunused-label -Wunused-value -Wvla")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native -mtune=native -fopenmp -D_GLIBCXX_PARALLEL -funroll-loops -flto -ffast-math -fno-signed-zeros -fno-trapping-math -floop-interchange -floop-block -floop-strip-mine -floop-parallelize-all -falign-functions -falign-loops -falign-jumps")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fno-omit-frame-pointer -fno-inline -fstack-protector-all -fsanitize=address -fsanitize=address")

# Folder structure
set(SRCDIR src)
set(INCDIR include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(sdl2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)
pkg_check_modules(glm REQUIRED IMPORTED_TARGET glm)

# Recursively search for source files
file(GLOB_RECURSE SRCS "${SRCDIR}/*.cpp" "${SRCDIR}/*.c")
# Recursively search for header files
file(GLOB_RECURSE HDRS "${INCDIR}/*.hpp" "${INCDIR}/*.h")

# Build targets
add_executable(graph main.cpp ${SRCS} ${HDRS})

# Find dependencies based on platform
# target_link_libraries(graph PRIVATE PkgConfig::sdl2)
target_link_libraries(graph PRIVATE PkgConfig::sdl2 PkgConfig::SDL2_ttf)
