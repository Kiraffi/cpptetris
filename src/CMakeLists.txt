# CMakeList.txt : CMake project for hellogl, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

include(${CMAKE_HOME_DIRECTORY}/cmake/my_cmake.cmake)
#print_variables()

# Add source to this project's executable.
add_executable (cpptetris WIN32 "main.cpp" "mygl.cpp" "mygl.h" "helpers.h" "myglfuncs.h")

target_link_libraries(cpptetris PRIVATE
    ${OPENGL_LIBRARIES}
	OpenGL::GL
	#MyLibraries
)