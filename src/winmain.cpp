
#include <stdio.h>
#include <Windows.h>

#include "gamemain.h"
#include "helpers.h"
#include "window.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002


static HINSTANCE mainInstance;
static HGLRC hglrc = 0;
static bool quit = false;
static HWND hwnd = 0;

typedef BOOL WINAPI wglSwapIntervalEXTFunc(int interval);
wglSwapIntervalEXTFunc *wglSwapIntervalEXT = nullptr;

typedef HGLRC WINAPI wglCreateContextAttribsARBFunc(HDC hDC, HGLRC hShareContext,
    const int *attribList);



LRESULT CALLBACK Wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


void *getProcAddress(const char *proc)
{
    void *func = wglGetProcAddress(proc);
    return func;
}




void printString(const char *str)
{
    OutputDebugStringA(str);
}




bool MyWindow::initWindow(const char *str)
{
    windowStr = str;

    WNDCLASS windowClass = {};
    static const char CLASS_NAME[] = "MyVeryOwnRandomWindowClassHere";

    windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = Wndproc;
    windowClass.hInstance = mainInstance;

    windowClass.lpszClassName = CLASS_NAME;

    RegisterClass(&windowClass);

    // Create the window.

    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        str,
        WS_OVERLAPPEDWINDOW,

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        mainInstance,
        NULL
    );

    if(hwnd == NULL)
    {
        return false;
    }
    ShowWindow(hwnd, SW_SHOWNORMAL);

    return true;
}

void MyWindow::deinitWindow()
{
    if(hglrc)
    {
        // make the rendering context not current
        wglMakeCurrent(NULL, NULL);

        // delete the rendering context
        wglDeleteContext(hglrc);
    }
    if(hwnd)
    {
        DestroyWindow(hwnd);
    }
}

bool MyWindow::initOpengl()
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
                }
            }
            else
            {
                createSuccess = 0;
            }
        }


        wglSwapIntervalEXT = (wglSwapIntervalEXTFunc *)wglGetProcAddress("wglSwapIntervalEXT");
        if(wglSwapIntervalEXT)
        {
            wglSwapIntervalEXT(1);
        }
    }

    ReleaseDC(hwnd, hdc);
    return createSuccess != 0;
}

void MyWindow::setVsync(bool vsync)
{
    if(wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(vsync ? 1 : 0);
    }
}


bool MyWindow::pollMessges()
{
    MSG msg = {};
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    running = !quit;
    return quit;
}

void MyWindow::updateWindowSize()
{
    RECT windowRect = {};
    if(GetWindowRect(hwnd, &windowRect) == 0)
    {
        width = 0;
        height = 0;
    }

    width = windowRect.right - windowRect.left;
    height = windowRect.bottom - windowRect.top;
}

void MyWindow::swapBuffers()
{
    HDC hdc = GetDC(hwnd);
    SwapBuffers(hdc);
    DeleteDC(hdc);
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

    mainInstance = mainInstance;

    runGameMain();


    return 0;
}
