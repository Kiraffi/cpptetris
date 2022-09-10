#pragma once

#include "mygl.h"

extern "C"
{
    extern void API glDrawArrays(GLenum mode, GLint first, GLsizei count);
    extern void API glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    extern void API glClear(GLbitfield mask);
    extern void API glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    extern void API glClearStencil(GLint s);
    extern void API glClearDepth(GLdouble depth);
    extern const GLubyte* API glGetString(GLenum name);
}
