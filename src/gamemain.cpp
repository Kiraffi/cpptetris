#include "gamemain.h"

#include "helpers.h"
#include "myglfuncs.h"
#include "window.h"


#include <chrono>



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




void createTriangle(GL &gl)
{
    static constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };


    gl.glGenBuffers(1, &VBO);

    gl.glGenVertexArrays(1, &VAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    gl.glBindVertexArray(VAO);

    gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    gl.glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    gl.glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    gl.glBindVertexArray(0);
}

void renderTriangle(GL &gl)
{
    gl.glUseProgram(shaderProgram);
    gl.glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void runGameLoop(MyWindow &window, GL &gl)
{
    window.setVsync(true);
    shaderProgram = createShaders(gl, vertexShaderSource, fragmentShaderSource);
    if(shaderProgram == 0)
    {
        return;
    }
    createTriangle(gl);

    window.running = true;

    auto prevTime = std::chrono::high_resolution_clock::now();
    while(window.running)
    {
        window.pollMessges();
        window.updateWindowSize();

        glViewport(0, 0, window.width, window.height);
        glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderTriangle(gl);
        window.swapBuffers();
        auto newTime = std::chrono::high_resolution_clock::now();

        print("Nanos: %ins\n", int(std::chrono::duration_cast<std::chrono::nanoseconds>(newTime - prevTime).count()));
        prevTime = newTime;
    }
}

void runGameMain()
{
    MyWindow window = {};

    if(!window.initWindow("Cpp Tetris"))
    {
        return;
    }

    if(!window.initOpengl())
    {
        window.deinitWindow();
        return;
    }
    GL gl;
    OpenGLInfo info = getOpenGLInfo(true);

    if(!loadFuncs(gl, info.extensions))
    {
        return;
    }


    print("Vendor: %s\n", info.vendor);


    runGameLoop(window, gl);

    window.deinitWindow();
}