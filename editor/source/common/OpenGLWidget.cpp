#include "./OpenGLWidget.h"
#include <qui/Timer.h>
#include <qui/log.h>

OpenGLWidget::OpenGLWidget(const QGLFormat& format, const GameInterface& gi)
        : QGLWidget(format)
        , timer(new qui::Timer())
        , gi(gi)
{
}

OpenGLWidget::~OpenGLWidget()
{
    delete timer;
}

void OpenGLWidget::initializeGL()
{
    if (gi.gameInit != nullptr)
    {
        gi.gameInit();
    }
}

void OpenGLWidget::paintGL()
{
    if (gi.gameUpdate != nullptr)
    {
        gi.gameUpdate(timer->getDeltaTime());
    }
    QGLWidget::paintGL();
    if (gi.gamePaint != nullptr)
    {
        gi.gamePaint();
    }
}

void OpenGLWidget::resizeGL(int w, int h)
{
    if (gi.gameSetWindowSize != nullptr)
    {
        gi.gameSetWindowSize(w, h);
    }
}

