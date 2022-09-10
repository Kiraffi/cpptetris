# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)
project ("cpptetris" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

#check for instruction/link time optimization supported
include(CheckIPOSupported)

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

#ADD_DEFINITIONS(-DCMAKE_GENERATOR_PLATFORM=x64)
#ADD_DEFINITIONS(-DCMAKE_GENERATOR_PLATFORM=x86)

#set(CMAKE_CXX_FLAGS_RELEASE "-O2")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g /d1reportTime")

# adding multiprocessor compilation, in case generating visual studio solution separately
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
#add_compile_options($<$<CXX_COMPILER_ID:MSVC>-ftime-ftrace)
if (WIN32)
    ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN=1)
    
endif (WIN32)



include(${PROJECT_SOURCE_DIR}/cmake/my_cmake.cmake)
#set(OpenGL_GL_PREFERENCE "GLVND")
#set(OpenGL_GL_PREFERENCE LEGACY)

if (UNIX)
    #do something
endif (UNIX)

find_package(OpenGL REQUIRED)


add_subdirectory("src")

#print_variables()
