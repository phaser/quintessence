// Copyright (C) 2013 Cristian Bidea
#include <qui/StandardGameEntry.h>
#include <qui/log.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <TCHAR.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <qui/GLWindow.h>
#include <qui/Timer.h>
#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>

/******************************************************************************
 Defines
******************************************************************************/
// #define NO_GDI 1 /* Remove the GDI functions */

#ifndef NO_GDI

// Windows class name to register
#define    WINDOW_CLASS _T("PVRShellClass")

#endif

// Index to bind the attributes to vertex shaders
#define VERTEX_ARRAY    0

/************************************************************************/
/* Global variables                                                     */
/************************************************************************/
// Variable set in the message handler to finish the demo
bool    g_bDemoDone = false;

// Windows variables
HWND                hWnd    = 0;
HDC                    hDC        = 0;

/************************************************************************/
/* Local functions forward declaration                                  */
/************************************************************************/
void initOpenGLES(HINSTANCE hInstance, qui::StandardGameEntry* game);
void cleanup();

/************************************************************************/
/* Local functions implementation                                        */
/************************************************************************/
bool lmousepressed = false;
/**
 * Processes messages for the main window
 * @param hWnd Handle to the window
 * @param message Specifies the message
 * @param wParam More info on the message
 * @param lParam More info on the message
 * @return LRESULT Result code to the OS
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  // NOLINT
{
    using qui::input::InputInterface;
    using qui::input::TouchInputEvent;
    int x, y;
    InputInterface ii;
    switch (message)
    {
        case WM_SYSCOMMAND:
        {
            switch (wParam)
            {
                case SC_SCREENSAVE:                    // Screensaver trying to start ?
                case SC_MONITORPOWER:                // Monitor trying to enter powersave ?
                return 0;                            // Prevent this from happening
            }
            break;
        }

        // Handles the close message when a user clicks the quit icon of the window
        case WM_CLOSE:
            g_bDemoDone = true;
            PostQuitMessage(0);
            return 1;

        case WM_LBUTTONDOWN:
        {
            lmousepressed = true;
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::DOWN, 0, x, y));
            break;
        }
        case WM_LBUTTONUP:
        {
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::UP, 0, x, y));
            lmousepressed = false;
            break;
        }
        case WM_MOUSEMOVE:
        {
            if (lmousepressed)
            {
                x = GET_X_LPARAM(lParam);
                y = GET_Y_LPARAM(lParam);
                ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::MOVE, 0, x, y));
            }
            break;
        }
        default:
            break;
    }

    // Calls the default window procedure for messages we did not handle
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 * Tests for an EGL error and prints it.
 */
bool testEGLError(char* pszLocation)
{
    /*
        eglGetError returns the last error that has happened using egl,
        not the status of the last called function. The user has to
        check after every single egl call or at least once every frame.
    */
    EGLint iErr = eglGetError();
    if (iErr != EGL_SUCCESS)
    {
        TCHAR pszStr[256];
        _stprintf(pszStr, _T("%s failed (%d).\n"), pszLocation, iErr);
        LOG(FATAL) << pszStr;
        return false;
    }

    return true;
}

/**
 * Main function of the program
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR *lpCmdLine, int nCmdShow)  // NOLINT
{
    initOpenGLES(hInstance, qui::game.get());
    qui::game->init();

    /* Games main loop */
    qui::Timer timer;
    uint64_t dtime = 0;
    qui::input::InputInterface ii;
    while (!g_bDemoDone)
    {
        dtime += timer.getDeltaTime();
        if (dtime > 30)  // limit to ~30 fps
        {
            ii.fireUpdateListeners();
            qui::game->update(dtime);
            qui::game->paint();
            eglSwapBuffers(qui::game->getWindow().getEGLDisplay(), qui::game->getWindow().getEGLSurface());
            dtime = 0;
        }
        // Managing the window messages
        MSG msg;
        PeekMessage(&msg, hWnd, NULL, NULL, PM_REMOVE);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    qui::game->cleanup();
    return 0;
}

/**
 * Initializes an open gl es context
 */
void initOpenGLES(HINSTANCE hInstance, qui::StandardGameEntry* game)
{
    // EGL variables
    EGLConfig            eglConfig    = 0;
    EGLContext            eglContext    = 0;
    EGLNativeWindowType    eglWindow    = 0;

    WNDCLASS sWC;
    sWC.style = CS_HREDRAW | CS_VREDRAW;
    sWC.lpfnWndProc = WndProc;
    sWC.cbClsExtra = 0;
    sWC.cbWndExtra = 0;
    sWC.hInstance = hInstance;
    sWC.hIcon = 0;
    sWC.hCursor = 0;
    sWC.lpszMenuName = 0;
    sWC.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    sWC.lpszClassName = WINDOW_CLASS;

    ATOM registerClass = RegisterClass(&sWC);
    if (!registerClass)
    {
        MessageBox(0, _T("Failed to register the window class"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
    }

    // Create the eglWindow
    RECT    sRect;
    SetRect(&sRect, 0, 0, game->getWindow().getWidth(), game->getWindow().getHeight());
    AdjustWindowRectEx(&sRect, WS_CAPTION | WS_SYSMENU, false, 0);
    hWnd = CreateWindow(WINDOW_CLASS
                      , _T(game->getWindow().getWindowName().c_str())
                      , WS_VISIBLE | WS_SYSMENU
                      , 0
                      , 0
                      , game->getWindow().getWidth()
                      , game->getWindow().getHeight()
                      , NULL
                      , NULL
                      , hInstance
                      , NULL);
    eglWindow = hWnd;

    // Get the associated device context
    hDC = GetDC(hWnd);
    if (!hDC)
    {
        MessageBox(0, _T("Failed to create the device context"), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
        cleanup();
    }

    EGLDisplay display = eglGetDisplay(hDC);

    if (display == EGL_NO_DISPLAY)
         display = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);

    game->getWindow().setEGLDisplay(display);

    EGLint iMajorVersion, iMinorVersion;
    if (!eglInitialize(game->getWindow().getEGLDisplay(), &iMajorVersion, &iMinorVersion))
    {
        MessageBox(0, _T("eglInitialize() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
        cleanup();
    }

    eglBindAPI(EGL_OPENGL_ES_API);
    if (!testEGLError("eglBindAPI"))
    {
        cleanup();
    }

    const EGLint pi32ConfigAttribs[] =
    {
        EGL_LEVEL,                0,
        EGL_SURFACE_TYPE,        EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES2_BIT,
        EGL_NATIVE_RENDERABLE,    EGL_FALSE,
        EGL_DEPTH_SIZE,            EGL_DONT_CARE,
        EGL_NONE
    };

    int iConfigs;
    if (!eglChooseConfig(game->getWindow().getEGLDisplay()
                       , pi32ConfigAttribs
                       , &eglConfig
                       , 1
                       , &iConfigs)
     || (iConfigs != 1))
    {
        MessageBox(0, _T("eglChooseConfig() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
        cleanup();
    }

    EGLSurface surface = eglCreateWindowSurface(
                            game->getWindow().getEGLDisplay(),
                            eglConfig,
                            eglWindow,
                            NULL);

    if (surface == EGL_NO_SURFACE)
    {
        eglGetError();  // Clear error
        surface = eglCreateWindowSurface(
                     game->getWindow().getEGLDisplay()
                   , eglConfig
                   , NULL
                   , NULL);
    }

    if (!testEGLError("eglCreateWindowSurface"))
    {
        cleanup();
    }
    game->getWindow().setEGLSurface(surface);

    EGLint ai32ContextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION
      , 2
      , EGL_NONE
    };
    eglContext = eglCreateContext(game->getWindow().getEGLDisplay(), eglConfig, NULL, ai32ContextAttribs);
    if (!testEGLError("eglCreateContext"))
    {
        cleanup();
    }

    qui::GLWindow window = game->getWindow();
    window.setEGLContext(eglContext);
    eglMakeCurrent(window.getEGLDisplay()
                 , window.getEGLSurface()
                 , window.getEGLSurface()
                 , window.getEGLContext());
    if (!testEGLError("eglMakeCurrent"))
    {
        cleanup();
    }
}

/**
 * Cleans up open gl context and exits with error code. This function is called 
 * on error.
 */
void cleanup()
{
    eglMakeCurrent(qui::game->getWindow().getEGLDisplay(), EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglTerminate(qui::game->getWindow().getEGLDisplay());

    // Release the device context
    if (hDC) ReleaseDC(hWnd, hDC);

    // Destroy the eglWindow
    if (hWnd) DestroyWindow(hWnd);
    exit(1);
}
