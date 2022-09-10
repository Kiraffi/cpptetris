
#pragma once

class MyWindow
{
public:
    bool initWindow(const char *str);
    void deinitWindow();

    bool initOpengl();

    void setVsync(bool vsync);
    bool pollMessges();

    void updateWindowSize();
    void swapBuffers();

    const char *windowStr;
    int width;
    int height;
    bool running;
};