#include "mygl.h"
#include "myglfuncs.h"

#include "helpers.h"

//#include <gl/GL.h>
unsigned int VBO = 0;
unsigned int VAO = 0;
unsigned int shaderProgram = 0;

const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    };
)";

const char *fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    };
)";



bool loadFuncs(const char *funcNames)
{
    glGenBuffers = (glGenBuffersFunc *)getProcAddress("glGenBuffers");
    glBindVertexArray = (glBindVertexArrayFunc *)getProcAddress("glBindVertexArray");
    glDeleteVertexArrays = (glDeleteVertexArraysFunc *)getProcAddress("glDeleteVertexArrays");
    glGenVertexArrays = (glGenVertexArraysFunc *)getProcAddress("glGenVertexArrays");
    glBindBuffer = (glBindBufferFunc *)getProcAddress("glBindBuffer");
    glDeleteBuffers = (glDeleteBuffersFunc *)getProcAddress("glDeleteBuffers");


    glBufferData = (glBufferDataFunc *)getProcAddress("glBufferData");
    glVertexAttribPointer = (glVertexAttribPointerFunc *)getProcAddress("glVertexAttribPointer");
    glEnableVertexAttribArray = (glEnableVertexAttribArrayFunc *)getProcAddress("glEnableVertexAttribArray");



    glDrawArrays = (glDrawArraysFunc *)getProcAddress("glDrawArrays");



    glLinkProgram = (glLinkProgramFunc *)getProcAddress("glLinkProgram");
    glShaderSource = (glShaderSourceFunc *)getProcAddress("glShaderSource");
    glUseProgram = (glUseProgramFunc *)getProcAddress("glUseProgram");

    glCompileShader = (glCompileShaderFunc *)getProcAddress("glCompileShader");
    glCreateProgram = (glCreateProgramFunc *)getProcAddress("glCreateProgram");
    glCreateShader = (glCreateShaderFunc *)getProcAddress("glCreateShader");
    glDeleteProgram = (glDeleteProgramFunc *)getProcAddress("glDeleteProgram");
    glDeleteShader = (glDeleteShaderFunc *)getProcAddress("glDeleteShader");
    glDetachShader = (glDetachShaderFunc *)getProcAddress("glDetachShader");
    glAttachShader = (glAttachShaderFunc *)getProcAddress("glAttachShader");
    glGetProgramiv = (glGetProgramivFunc *)getProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (glGetProgramInfoLogFunc *)getProcAddress("glGetProgramInfoLog");
    glGetShaderiv = (glGetShaderivFunc *)getProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (glGetShaderInfoLogFunc *)getProcAddress("glGetShaderInfoLog");
    glGetShaderSource = (glGetShaderSourceFunc *)getProcAddress("glGetShaderSource");






    return glGenBuffers &&
        glBindVertexArray &&
        glDeleteVertexArrays &&
        glGenVertexArrays &&
        glBindBuffer &&
        glDeleteBuffers &&
        glBufferData &&
        glVertexAttribPointer &&
        glEnableVertexAttribArray &&

        glDrawArrays &&

        glLinkProgram &&
        glShaderSource &&
        glUseProgram &&

        glCompileShader &&
        glCreateProgram &&
        glCreateShader &&
        glDeleteProgram &&
        glDeleteShader &&
        glDetachShader &&
        glAttachShader &&
        glGetProgramiv &&
        glGetProgramInfoLog &&
        glGetShaderiv &&
        glGetShaderInfoLog &&
        glGetShaderSource 

        ;
}



bool createShaders()
{
    // build and compile our shader program
// ------------------------------------
// vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512] = {};
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        print( "Vertex shader compilation failed\n%s\n", infoLog);
        return false;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        print("Fragment shader compilation failed\n%s\n", infoLog);
        return false;
    }

    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    
    if(!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        print("Shader linking failed\n%s\n", infoLog);
        return false;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}



void createTriangle()
{
    static constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

 
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO);
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


}

void renderTriangle()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}