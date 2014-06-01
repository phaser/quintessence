#include "./OpenGLWidget.h"
#include <qui/Timer.h>
#include <qui/log.h>

OpenGLWidget::OpenGLWidget(const QGLFormat& format)
        : QGLWidget(format)
        , timer(new qui::Timer())
{
}

OpenGLWidget::~OpenGLWidget()
{
    delete timer;
}

void OpenGLWidget::initializeGL()
{
}

void OpenGLWidget::paintGL()
{
    QGLWidget::paintGL();
}

void OpenGLWidget::resizeGL(int w, int h)
{
//    game->getWindow().setSize(glm::vec2(w, h));
//    game->onSystemEvent(WINDOW_RESIZED);
}


