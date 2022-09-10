#pragma once

#include "mygl.h"

typedef void API glDrawArraysFunc(GLenum mode, GLint first, GLsizei count);
static glDrawArraysFunc *glDrawArrays = nullptr;


