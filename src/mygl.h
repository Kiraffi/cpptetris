#pragma once



struct OpenGLInfo
{
    char *vendor;
    char *renderer;
    char *version;
    char *shadingLanguageVersion;
    char *extensions;
};


#ifdef _WIN64
    typedef signed   long long int khronos_intptr_t;
    typedef unsigned long long int khronos_uintptr_t;
    typedef signed   long long int khronos_ssize_t;
    typedef unsigned long long int khronos_usize_t;
#else
    typedef signed   long  int     khronos_intptr_t;
    typedef unsigned long  int     khronos_uintptr_t;
    typedef signed   long  int     khronos_ssize_t;
    typedef unsigned long  int     khronos_usize_t;
#endif

    typedef unsigned int GLenum;
    typedef unsigned int GLbitfield;
    typedef unsigned char GLboolean;
    typedef void GLvoid;
    typedef int GLint;
    typedef unsigned int GLuint;
    typedef int GLsizei;
    typedef unsigned int GLenum;
    typedef khronos_ssize_t GLsizeiptr;
    typedef char GLchar;
    typedef float GLfloat;
    typedef double GLdouble;
    typedef unsigned char GLubyte;

#ifndef NULL
#define NULL 0
#endif

#define API __stdcall

#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_FALSE 0
#define GL_TRUE 1

#define GL_POINTS 0x0000
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_STRIP 0x0003
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006
#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207
#define GL_ZERO 0
#define GL_ONE 1


#define GL_ARRAY_BUFFER 0x8892
#define GL_STREAM_DRAW 0x88E0
#define GL_STREAM_READ 0x88E1
#define GL_STREAM_COPY 0x88E2
#define GL_STATIC_DRAW 0x88E4
#define GL_STATIC_READ 0x88E5
#define GL_STATIC_COPY 0x88E6
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_DYNAMIC_COPY 0x88EA

#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPUTE_SHADER 0x91B9


#define GL_VERTEX_SHADER_BIT 0x00000001
#define GL_FRAGMENT_SHADER_BIT 0x00000002
#define GL_COMPUTE_SHADER_BIT 0x00000020

#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82

#define GL_VENDOR 0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02
#define GL_EXTENSIONS 0x1F03
#define GL_SHADING_LANGUAGE_VERSION_ARB 0x8B8C

typedef void API glGenBuffersFunc(GLsizei n, GLuint *buffers);
typedef void API glBindVertexArrayFunc(GLuint array);
typedef void API glDeleteVertexArraysFunc(GLsizei n, const GLuint *arrays);
typedef void API glGenVertexArraysFunc(GLsizei n, GLuint *arrays);
typedef void API glBindBufferFunc(GLenum target, GLuint buffer);
typedef void API glDeleteBuffersFunc(GLsizei n, const GLuint *buffers);
typedef void API glBufferDataFunc(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void API glVertexAttribPointerFunc(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void API glEnableVertexAttribArrayFunc(GLuint index);
typedef void API glLinkProgramFunc(GLuint program);
typedef void API glShaderSourceFunc(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
typedef void API glUseProgramFunc(GLuint program);
typedef void API glCompileShaderFunc(GLuint shader);
typedef GLuint API glCreateProgramFunc(void);
typedef GLuint API glCreateShaderFunc(GLenum type);
typedef void API glDeleteProgramFunc(GLuint program);
typedef void API glDeleteShaderFunc(GLuint shader);
typedef void API glDetachShaderFunc(GLuint program, GLuint shader);
typedef void API glAttachShaderFunc(GLuint program, GLuint shader);
typedef void API glGetProgramivFunc(GLuint program, GLenum pname, GLint *params);
typedef void API glGetProgramInfoLogFunc(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void API glGetShaderivFunc(GLuint shader, GLenum pname, GLint *params);
typedef void API glGetShaderInfoLogFunc(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void API glGetShaderSourceFunc(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);

struct GL
{
    glGenBuffersFunc *glGenBuffers = nullptr;
    glBindVertexArrayFunc *glBindVertexArray = nullptr;
    glDeleteVertexArraysFunc *glDeleteVertexArrays = nullptr;
    glGenVertexArraysFunc *glGenVertexArrays = nullptr;
    glBindBufferFunc *glBindBuffer = nullptr;
    glDeleteBuffersFunc *glDeleteBuffers = nullptr;
    glBufferDataFunc *glBufferData = nullptr;
    glVertexAttribPointerFunc *glVertexAttribPointer = nullptr;

    glEnableVertexAttribArrayFunc *glEnableVertexAttribArray = nullptr;
    glLinkProgramFunc *glLinkProgram = nullptr;
    glShaderSourceFunc *glShaderSource = nullptr;
    glUseProgramFunc *glUseProgram = nullptr;

    glCompileShaderFunc *glCompileShader = nullptr;
    glCreateProgramFunc *glCreateProgram = nullptr;
    glCreateShaderFunc *glCreateShader = nullptr;
    glDeleteProgramFunc *glDeleteProgram = nullptr;
    glDeleteShaderFunc *glDeleteShader = nullptr;
    glDetachShaderFunc *glDetachShader = nullptr;
    glAttachShaderFunc *glAttachShader = nullptr;

    glGetProgramivFunc *glGetProgramiv = nullptr;
    glGetProgramInfoLogFunc *glGetProgramInfoLog = nullptr;
    glGetShaderivFunc *glGetShaderiv = nullptr;
    glGetShaderInfoLogFunc *glGetShaderInfoLog = nullptr;
    glGetShaderSourceFunc *glGetShaderSource = nullptr;
};

bool loadFuncs(GL &gl, const char *extensions);

OpenGLInfo getOpenGLInfo(bool isModernContext);


unsigned int createShaders(GL &gl, const char *vertexShaderSource, const char *fragmentShaderSource);
