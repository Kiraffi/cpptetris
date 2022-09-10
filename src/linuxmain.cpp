#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include "gamemain.h"
#include "helpers.h"
#include "window.h"

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092

typedef GLXContext glXCreateContextAttribsARBProc(Display*, GLXFBConfig, GLXContext, Bool, const int*);
typedef void glXSwapIntervalEXTFunc(Display *dpy, GLXDrawable drawable, int interval);
static glXSwapIntervalEXTFunc *glXSwapIntervalEXT = nullptr;

static bool quit = false;



Display                 *dpy;
Window                  root;
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;


int main(int argc, char *argv[])
{
    runGameMain();
}





void *getProcAddress(const char *proc)
{
    void* func = (void *)glXGetProcAddressARB((const GLubyte *)(proc));
    return func;
}




void printString(const char *str)
{
    printf("%s", str);
}




bool MyWindow::initWindow(const char *str)
{
    windowStr = str;

    dpy = XOpenDisplay(NULL);

    if(dpy == NULL)
    {
        printf("\n\tcannot connect to X server\n\n");
        exit(0);
    }




  // Get a matching FB config
  static int visualAttribs[] =
    {
      GLX_X_RENDERABLE    , True,
      GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
      GLX_RENDER_TYPE     , GLX_RGBA_BIT,
      GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
      GLX_RED_SIZE        , 8,
      GLX_GREEN_SIZE      , 8,
      GLX_BLUE_SIZE       , 8,
      GLX_ALPHA_SIZE      , 8,
      GLX_DEPTH_SIZE      , 24,
      GLX_STENCIL_SIZE    , 8,
      GLX_DOUBLEBUFFER    , True,
      //GLX_SAMPLE_BUFFERS  , 1,
      //GLX_SAMPLES         , 4,
      None
    };

    int glx_major, glx_minor;

    // FBConfigs were added in GLX version 1.3.
    if ( !glXQueryVersion( dpy, &glx_major, &glx_minor ) ||
        ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
    {
        printf("Invalid GLX version");
        exit(1);
    }
    int fbCount;
    GLXFBConfig* fbc = glXChooseFBConfig(dpy, DefaultScreen(dpy), visualAttribs, &fbCount);
    if (!fbc || fbCount < 1)
    {
        exit(1);
    }
    GLXFBConfig bestFbc = fbc[0];

    vi = glXGetVisualFromFBConfig( dpy, bestFbc );
    if(vi == NULL)
    {
        printf("\n\tno appropriate visual found\n\n");
        exit(0);
    }
    else
    {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
    }
    root = RootWindow(dpy, vi->screen);
    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root,
        0, 0, 600, 600, 0, vi->depth, InputOutput,
        vi->visual, CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, str);


    glXCreateContextAttribsARBProc *glXCreateContextAttribsARB =
        (glXCreateContextAttribsARBProc *)getProcAddress("glXCreateContextAttribsARB" );
    if(glXCreateContextAttribsARB)
    {
        int contextAttribs[] =
        {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
            GLX_CONTEXT_MINOR_VERSION_ARB, 5,
            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | GLX_CONTEXT_DEBUG_BIT_ARB,

            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,

            None
        };

        printf( "Creating context\n" );
        glc = glXCreateContextAttribsARB( dpy, bestFbc, 0,
            True, contextAttribs );
    }
    else
    {
        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    }

    glXMakeCurrent(dpy, win, glc);

    glXSwapIntervalEXT =
        (glXSwapIntervalEXTFunc *)getProcAddress("glXSwapIntervalEXT" );


    return true;
}

void MyWindow::deinitWindow()
{
    glXMakeCurrent( dpy, 0, 0 );
    glXDestroyContext( dpy, glc );

    XDestroyWindow( dpy, win );
    XFreeColormap( dpy, cmap );
    XCloseDisplay( dpy );
}

bool MyWindow::initOpengl()
{
   return true;
}

void MyWindow::setVsync(bool vsync)
{
    if(glXSwapIntervalEXT)
    {
        glXSwapIntervalEXT(dpy, win, vsync ? 1 : 0);
    }
}


bool MyWindow::pollMessges()
{
    while(XPending(dpy))
    {
        XNextEvent(dpy, &xev);
        if(xev.type == Expose)
        {
            //return false;
        }

        else if(xev.type == KeyPress)
        {
            quit = true;
            running = false;
            return true;
        }
    }
   return false;
}

void MyWindow::updateWindowSize()
{
    XGetWindowAttributes(dpy, win, &gwa);
    width = gwa.width;
    height = gwa.height;
}

void MyWindow::swapBuffers()
{
    glXSwapBuffers(dpy, win);
}





