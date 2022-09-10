#include "mygl.h"
#include "myglfuncs.h"

#include "helpers.h"


OpenGLInfo getOpenGLInfo(bool isModernContext)
{
    OpenGLInfo info = {};
    info.vendor = (char *)glGetString(GL_VENDOR);
    info.renderer = (char *)glGetString(GL_RENDERER);
    info.version = (char *)glGetString(GL_VERSION);
    if(isModernContext)
    {
        info.shadingLanguageVersion = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
    }
    info.extensions = (char *)glGetString(GL_EXTENSIONS);
    /*
    char *cStart = info.extensions;
    char *c = cStart;
    while(c && cStart)
    {
        if(*c < 32 || *c >= 128)
            break;

        if(isspace(*c))
        {
            char str[LOG_LEN] = {};
            size_t strLen = intptr_t(c) - intptr_t(cStart);
            if(strLen < 2)
            {
                break;
            }
            strLen = strLen < LOG_LEN - 1 ? strLen : LOG_LEN - 1;
            memcpy(str, cStart, strLen);
            print("Extension: %s\n", str);
            cStart = c + 1;
        }

        ++c;
    }
    */
    return info;
}


static unsigned int compileShader(GL &gl, int shaderType, const char *shaderSourceText)
{
    unsigned int shader = gl.glCreateShader(shaderType);
    gl.glShaderSource(shader, 1, &shaderSourceText, nullptr);
    gl.glCompileShader(shader);

    int success = 0;
    gl.glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512] = {};
        gl.glGetShaderInfoLog(shader, 512, NULL, infoLog);
        switch(shaderType)
        {
            case GL_VERTEX_SHADER:
            print("Vertex shader compilation failed\n%s\n", infoLog);
            break;

            case GL_FRAGMENT_SHADER:
            print("Fragment shader compilation failed\n%s\n", infoLog);
            break;

            default:
            break;
        }
        
        return 0;
    }
    return shader;
}


bool loadFuncs(GL &gl, const char* extensions)
{
    gl.glGenBuffers = (glGenBuffersFunc *)getProcAddress("glGenBuffers");
    gl.glBindVertexArray = (glBindVertexArrayFunc *)getProcAddress("glBindVertexArray");
    gl.glDeleteVertexArrays = (glDeleteVertexArraysFunc *)getProcAddress("glDeleteVertexArrays");
    gl.glGenVertexArrays = (glGenVertexArraysFunc *)getProcAddress("glGenVertexArrays");
    gl.glBindBuffer = (glBindBufferFunc *)getProcAddress("glBindBuffer");
    gl.glDeleteBuffers = (glDeleteBuffersFunc *)getProcAddress("glDeleteBuffers");


    gl.glBufferData = (glBufferDataFunc *)getProcAddress("glBufferData");
    gl.glVertexAttribPointer = (glVertexAttribPointerFunc *)getProcAddress("glVertexAttribPointer");
    gl.glEnableVertexAttribArray = (glEnableVertexAttribArrayFunc *)getProcAddress("glEnableVertexAttribArray");

    gl.glLinkProgram = (glLinkProgramFunc *)getProcAddress("glLinkProgram");
    gl.glShaderSource = (glShaderSourceFunc *)getProcAddress("glShaderSource");
    gl.glUseProgram = (glUseProgramFunc *)getProcAddress("glUseProgram");

    gl.glCompileShader = (glCompileShaderFunc *)getProcAddress("glCompileShader");
    gl.glCreateProgram = (glCreateProgramFunc *)getProcAddress("glCreateProgram");
    gl.glCreateShader = (glCreateShaderFunc *)getProcAddress("glCreateShader");
    gl.glDeleteProgram = (glDeleteProgramFunc *)getProcAddress("glDeleteProgram");
    gl.glDeleteShader = (glDeleteShaderFunc *)getProcAddress("glDeleteShader");
    gl.glDetachShader = (glDetachShaderFunc *)getProcAddress("glDetachShader");
    gl.glAttachShader = (glAttachShaderFunc *)getProcAddress("glAttachShader");
    gl.glGetProgramiv = (glGetProgramivFunc *)getProcAddress("glGetProgramiv");
    gl.glGetProgramInfoLog = (glGetProgramInfoLogFunc *)getProcAddress("glGetProgramInfoLog");
    gl.glGetShaderiv = (glGetShaderivFunc *)getProcAddress("glGetShaderiv");
    gl.glGetShaderInfoLog = (glGetShaderInfoLogFunc *)getProcAddress("glGetShaderInfoLog");
    gl.glGetShaderSource = (glGetShaderSourceFunc *)getProcAddress("glGetShaderSource");

    return 
        gl.glGenBuffers &&
        gl.glBindVertexArray &&
        gl.glDeleteVertexArrays &&
        gl.glGenVertexArrays &&
        gl.glBindBuffer &&
        gl.glDeleteBuffers &&
        gl.glBufferData &&
        gl.glVertexAttribPointer &&
        gl.glEnableVertexAttribArray &&

        gl.glLinkProgram &&
        gl.glShaderSource &&
        gl.glUseProgram &&
        
        gl.glCompileShader &&
        gl.glCreateProgram &&
        gl.glCreateShader &&
        gl.glDeleteProgram &&
        gl.glDeleteShader &&
        gl.glDetachShader &&
        gl.glAttachShader &&
        gl.glGetProgramiv &&
        gl.glGetProgramInfoLog &&
        gl.glGetShaderiv &&
        gl.glGetShaderInfoLog &&
        gl.glGetShaderSource 

        ;

}


unsigned int  createShaders(GL &gl, const char *vertexShaderSource, const char *fragmentShaderSource)
{
    unsigned int vertexShader = compileShader(gl, GL_VERTEX_SHADER, vertexShaderSource);
    if(vertexShader == 0)
    {
        return 0;
    }

    unsigned int fragmentShader = compileShader(gl, GL_FRAGMENT_SHADER, fragmentShaderSource);
    if(fragmentShader == 0)
    {
        gl.glDeleteShader(vertexShader);
        return 0;
    }

    // link shaders
    unsigned int shaderProgram = gl.glCreateProgram();
    gl.glAttachShader(shaderProgram, vertexShader);
    gl.glAttachShader(shaderProgram, fragmentShader);
    gl.glLinkProgram(shaderProgram);
    // check for linking errors
    int success = 0;
    gl.glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512] = {};
        gl.glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        print("Shader linking failed\n%s\n", infoLog);

        gl.glDeleteShader(vertexShader);
        gl.glDeleteShader(fragmentShader);
        return 0;
    }
    gl.glDeleteShader(vertexShader);
    gl.glDeleteShader(fragmentShader);

    return shaderProgram;
}
