# CMakeList.txt : CMake project for hellogl, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

include(${CMAKE_HOME_DIRECTORY}/cmake/my_cmake.cmake)
#print_variables()

if (WIN32)
	set(MAIN_CPP "winmain.cpp")
    set(IncludeX11)
endif(WIN32)
if (UNIX)
	set(MAIN_CPP "linuxmain.cpp")
    set(IncludeX11 "-lX11")
endif(UNIX)

# Add source to this project's executable.
add_executable (cpptetris WIN32 ${MAIN_CPP} "mygl.cpp" "mygl.h" "helpers.h" "myglfuncs.h" "window.h" "gamemain.cpp" "gamemain.h")

target_link_libraries(cpptetris PRIVATE
    ${OPENGL_LIBRARIES}
	OpenGL::GL
    ${IncludeX11}
	#MyLibraries
)