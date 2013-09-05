// Copyright (C) 2012 Cristian Bidea
#include <qui/StandardGameEntry.h>
#include <qui/log.h>
#include <qui/Timer.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>

namespace qui
{
}  // namespace qui

#include <GL/glfw.h>

bool leftDown;

void onMousePress(int button, int event)
{
    using qui::input::InputInterface;
    using qui::input::TouchInputEvent;
    int x, y;
    InputInterface ii;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        glfwGetMousePos(&x, &y);
        if (event == GLFW_PRESS)
        {
            leftDown = true;
            ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::DOWN, 0, x, y));
        }
        else if (event == GLFW_RELEASE)
        {
            leftDown = false;
            ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::UP, 0, x, y));
        }
    }
}

void onMouseMove(int x, int y)
{
    using qui::input::InputInterface;
    using qui::input::TouchInputEvent;
    InputInterface ii;
    if (leftDown)
    {
        ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::MOVE, 0, x, y));
    }
}

int main(void)
{
    int running = GL_TRUE;

    // Initialize GLFW
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    // Open an OpenGL window
    if (!glfwOpenWindow(qui::game->getWindow().getSize().x
                      , qui::game->getWindow().getSize().y
                      , 0, 0, 0, 0, 0, 0
                      , GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    qui::game->init();
    qui::Timer timer;
    qui::input::InputInterface ii;
    leftDown = false;
    glfwSetMouseButtonCallback(onMousePress);
    glfwSetMousePosCallback(onMouseMove);
    // Main loop
    while (running)
    {
        ii.fireUpdateListeners();
        qui::game->update(timer.getDeltaTime());
        qui::game->paint();

        // Swap front and back rendering buffers
        glfwSwapBuffers();

        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) &&
        glfwGetWindowParam(GLFW_OPENED);
    }

    qui::game->cleanup();
    // Close window and terminate GLFW
    glfwTerminate();

    // Exit program
    exit(EXIT_SUCCESS);
}

