#include <stdio.h>

#include <chrono>
#include <Windows.h>
#include <gl/GL.h>

#include "helpers.h"
#include "mygl.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define GL_SHADING_LANGUAGE_VERSION_ARB 0x8B8C

static HGLRC hglrc = 0;
static bool quit = false;

//typedef BOOL WINAPI wglSwapIntervalEXTFunc(int interval);
//wglSwapIntervalEXTFunc *wglSwapIntervalEXT = nullptr;

typedef HGLRC WINAPI wglCreateContextAttribsARBFunc(HDC hDC, HGLRC hShareContext,
    const int *attribList);


void *getProcAddress(const char *proc)
{
    void *func = wglGetProcAddress(proc);
    return func;
}


struct OpenGLInfo
{
    char *vendor;
    char *renderer;
    char *version;
    char *shadingLanguageVersion;
    char *extensions;
};

void printString(const char *str)
{
    OutputDebugStringA(str);
}

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

    return info;
}

bool win32InitOpenglContext(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR desiredPixelFormat{
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
        .iPixelType = LPD_TYPE_RGBA,
        .cColorBits = 24,
        .cAlphaBits = 8,
        .cDepthBits = 32,
        .iLayerType = PFD_MAIN_PLANE
    };

    int chosenPixelFormatIndex = ChoosePixelFormat(hdc, &desiredPixelFormat);
    
    PIXELFORMATDESCRIPTOR chosenPixelFormat{};
    DescribePixelFormat(hdc, chosenPixelFormatIndex, sizeof(PIXELFORMATDESCRIPTOR), &chosenPixelFormat);
    SetPixelFormat(hdc, chosenPixelFormatIndex, &chosenPixelFormat);

    

    // create a rendering context  
    hglrc = wglCreateContext(hdc);
    BOOL createSuccess = wglMakeCurrent(hdc, hglrc);
    // make it the calling thread's current rendering context 
    if(createSuccess)
    {
        OpenGLInfo info = getOpenGLInfo(false);
        print("Vendor: %s", info.vendor);

        wglCreateContextAttribsARBFunc *wglCreateContextAttribsARB = 
            (wglCreateContextAttribsARBFunc *)wglGetProcAddress("wglCreateContextAttribsARB");
        if(wglCreateContextAttribsARB)
        {
            int attribs[] =
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, 5,
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,

                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,

                0,
            };

            HGLRC modernContext = wglCreateContextAttribsARB(hdc, 0, attribs);
            if(modernContext)
            {
                if(wglMakeCurrent(hdc, modernContext))
                {
                    wglDeleteContext(hglrc);
                    hglrc = modernContext;

                    info = getOpenGLInfo(true);

                    if(!loadFuncs(info.extensions))
                    {
                        createSuccess = false;
                    }
                }
            }
            else
            {
                createSuccess = false;
            }
        }


        glSwapIntervalEXT =  (glSwapIntervalEXTFunc *)wglGetProcAddress("wglSwapIntervalEXT");
        if(glSwapIntervalEXT)
        {
            glSwapIntervalEXT(1);
        }
    }

    ReleaseDC(hwnd, hdc);
    return createSuccess;
}

void win32DelteOpenglContext()
{
    if(hglrc)
    {
        // make the rendering context not current  
        wglMakeCurrent(NULL, NULL);

        // delete the rendering context  
        wglDeleteContext(hglrc);
    }
}

LRESULT CALLBACK Wndproc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    LRESULT result = 0;
    switch(uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            quit = true;
            break;
        }

        case WM_CLOSE:
        {
            PostQuitMessage(0);
            quit = true;
            break;
        }

        case WM_SIZE:
        {

            break;
        }

        case WM_ACTIVATEAPP:
        {

            break;
        }

        default:
        {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
        }
    }

    return result;
}

INT WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow)
{
    print("Hello from winmain\n");

    WNDCLASS windowClass = {};
    static const char CLASS_NAME[] = "CPPTetrisWindowClass";

    windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = Wndproc;
    windowClass.hInstance = hInstance;

    windowClass.lpszClassName = CLASS_NAME;

    RegisterClass(&windowClass);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "CPP Tetris",
        WS_OVERLAPPEDWINDOW,

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    if(!win32InitOpenglContext(hwnd))
    {
        return 0;
    }

    if(!createShaders())
    {
        return 0;
    }
    createTriangle();

    RECT windowRect = {};

   
    

    HDC hdc = GetDC(hwnd);
    auto prevTime = std::chrono::high_resolution_clock::now();
    while(!quit)
    {
        MSG msg = {};
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if(GetWindowRect(hwnd, &windowRect) == 0)
        {
            return 0;
        }

        int windowWidth = windowRect.right - windowRect.left;
        int windowHeight = windowRect.bottom - windowRect.top;

        glViewport(0, 0, windowWidth, windowHeight);
        glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderTriangle();
        SwapBuffers(hdc);
        auto newTime = std::chrono::high_resolution_clock::now();

        //print("Nanos: %ins\n", int(std::chrono::duration_cast<std::chrono::nanoseconds>(newTime - prevTime).count()));
        prevTime = newTime;
    }
    DeleteDC(hdc);
    
    return 0;
}
