// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIGameEntry.
//
//    QUIGameEntry is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIGameEntry is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIGameEntry.  If not, see <http://www.gnu.org/licenses/>.

#include "./OpenGLWidget.h"
#include <qui/StandardGameEntry.h>
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
    qui::game->init();
}

void OpenGLWidget::paintGL()
{
    QGLWidget::paintGL();
    qui::game->update(timer->getDeltaTime());
    qui::game->paint();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    qui::game->getWindow().setSize(glm::vec2(w, h));
    qui::game->onSystemEvent(qui::WINDOW_RESIZED);
}


