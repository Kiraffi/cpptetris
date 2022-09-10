#pragma once

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

typedef int API glSwapIntervalEXTFunc(int interval);
static glSwapIntervalEXTFunc *glSwapIntervalEXT = nullptr;

typedef void API glGenBuffersFunc(GLsizei n, GLuint *buffers);
static glGenBuffersFunc *glGenBuffers = nullptr;

typedef void API glBindVertexArrayFunc(GLuint array);
static glBindVertexArrayFunc *glBindVertexArray = nullptr;

typedef void API glDeleteVertexArraysFunc(GLsizei n, const GLuint *arrays);
static glDeleteVertexArraysFunc* glDeleteVertexArrays = nullptr;

typedef void API glGenVertexArraysFunc(GLsizei n, GLuint *arrays);
static glGenVertexArraysFunc *glGenVertexArrays = nullptr;


typedef void API glBindBufferFunc(GLenum target, GLuint buffer);
static glBindBufferFunc *glBindBuffer = nullptr;

typedef void API glDeleteBuffersFunc(GLsizei n, const GLuint *buffers);
static glDeleteBuffersFunc *glDeleteBuffers = nullptr;

typedef void API glBufferDataFunc(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
static glBufferDataFunc *glBufferData = nullptr;

typedef void API glVertexAttribPointerFunc(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
static glVertexAttribPointerFunc *glVertexAttribPointer = nullptr;

typedef void API glEnableVertexAttribArrayFunc(GLuint index);
static glEnableVertexAttribArrayFunc *glEnableVertexAttribArray = nullptr;

typedef void API glLinkProgramFunc(GLuint program);
static glLinkProgramFunc *glLinkProgram = nullptr;

typedef void API glShaderSourceFunc(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
static glShaderSourceFunc *glShaderSource = nullptr;

typedef void API glUseProgramFunc(GLuint program);
static glUseProgramFunc *glUseProgram = nullptr;








typedef void API glCompileShaderFunc(GLuint shader);
static glCompileShaderFunc *glCompileShader = nullptr;

typedef GLuint API glCreateProgramFunc(void);
static glCreateProgramFunc *glCreateProgram = nullptr;

typedef GLuint API glCreateShaderFunc(GLenum type);
static glCreateShaderFunc *glCreateShader = nullptr;

typedef void API glDeleteProgramFunc(GLuint program);
static glDeleteProgramFunc *glDeleteProgram = nullptr;

typedef void API glDeleteShaderFunc(GLuint shader);
static glDeleteShaderFunc *glDeleteShader = nullptr;

typedef void API glDetachShaderFunc(GLuint program, GLuint shader);
static glDetachShaderFunc *glDetachShader = nullptr;

typedef void API glAttachShaderFunc(GLuint program, GLuint shader);
static glAttachShaderFunc *glAttachShader = nullptr;



typedef void API glGetProgramivFunc(GLuint program, GLenum pname, GLint *params);
static glGetProgramivFunc *glGetProgramiv = nullptr;

typedef void API glGetProgramInfoLogFunc(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
static glGetProgramInfoLogFunc *glGetProgramInfoLog = nullptr;

typedef void API glGetShaderivFunc(GLuint shader, GLenum pname, GLint *params);
static glGetShaderivFunc *glGetShaderiv = nullptr;

typedef void API glGetShaderInfoLogFunc(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
static glGetShaderInfoLogFunc *glGetShaderInfoLog = nullptr;

typedef void API glGetShaderSourceFunc(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
static glGetShaderSourceFunc *glGetShaderSource = nullptr;

bool loadFuncs(const char *funcNames);


bool createShaders();
void* getProcAddress(const char *funcName);

void createTriangle();
void renderTriangle();