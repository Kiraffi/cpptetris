#pragma once

#include "mygl.h"

extern "C"
{
    extern void GLAPI glDrawArrays(GLenum mode, GLint first, GLsizei count);
    extern void GLAPI glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    extern void GLAPI glClear(GLbitfield mask);
    extern void GLAPI glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    extern void GLAPI glClearStencil(GLint s);
    extern void GLAPI glClearDepth(GLdouble depth);
    extern const GLubyte* GLAPI glGetString(GLenum name);
}
