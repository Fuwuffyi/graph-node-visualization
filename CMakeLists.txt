cmake_minimum_required(VERSION 3.29)
project(raytracer)

# Compiler options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wshadow -Wold-style-cast -Wcast-align -Wformat=2 -Wconversion -Wunreachable-code -Wno-unused-parameter -Wno-unused-variable -Waddress -Wdangling-pointer -Wformat-nonliteral -Wnoexcept -Wctor-dtor-privacy -Wenum-compare -Wsign-compare -Wswitch -Wnoexcept-type -Wno-overloaded-virtual -Wcast-qual -Wcomment -Woverloaded-virtual -Wreorder -Warray-bounds -Wchar-subscripts -Wconversion-null -Wdeprecated -Wfloat-equal -Winit-self -Wlogical-op -Wmissing-braces -Wmissing-field-initializers -Wmissing-include-dirs -Wno-narrowing -Wredundant-decls -Wsign-conversion -Wswitch-default -Wundef -Wunused-but-set-variable -Wunused-function -Wunused-label -Wunused-value -Wvla")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native -mtune=native -fopenmp -D_GLIBCXX_PARALLEL -funroll-loops -flto -ffast-math -fno-signed-zeros -fno-trapping-math -floop-interchange -floop-block -floop-strip-mine -floop-parallelize-all -falign-functions -falign-loops -falign-jumps")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fno-omit-frame-pointer -fno-inline -fstack-protector-all -fsanitize=address -fsanitize=address")

# Folder structure
set(SRCDIR src)
set(INCDIR include)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)

# Recursively search for source files
file(GLOB_RECURSE SRCS "${SRCDIR}/*.cpp" "${SRCDIR}/*.c")
# Recursively search for header files
file(GLOB_RECURSE HDRS "${INCDIR}/*.hpp" "${INCDIR}/*.h")

include(FetchContent)
# Add FetchContent for GLM
FetchContent_Declare(
   glm
   GIT_REPOSITORY https://github.com/g-truc/glm.git
   GIT_TAG        master
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
   sdl
   GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
   GIT_TAG        release-2.30.3
)
FetchContent_MakeAvailable(sdl)

# Disable library warnings
set_source_files_properties(${glm_SOURCE_DIR}/* PROPERTIES COMPILE_FLAGS -w)
set_source_files_properties(${sdl_SOURCE_DIR}/* PROPERTIES COMPILE_FLAGS -w)

# Include directories
include_directories(SYSTEM ${glm_SOURCE_DIR} SYSTEM ${sdl_SOURCE_DIR})

# Build targets
add_executable(graph main.cpp ${SRCS} ${HDRS})

# Find dependencies based on platform
target_link_libraries(graph SDL2 SDL2main)
