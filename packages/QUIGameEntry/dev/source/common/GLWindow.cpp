// Copyright (C) 2012 Cristian Bidea
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
#include <qui/GLWindow.h>
#include <string>

#ifndef NO_GDI
// Windows class name to register
#define    WINDOW_CLASS _T("PVRShellClass")
#endif

namespace qui
{
/* ======================================================================= *
 * Public Functions Implementation
 * ======================================================================= */
GLWindow::GLWindow(std::string name, int width, int height)
    : windowName(name)
    , size(width, height)
{
}

GLWindow::~GLWindow()
{
}

GLWindow& GLWindow::operator=(const GLWindow& win)
{
    this->windowName = win.windowName;
    this->size = win.size;
    return *this;
}

void GLWindow::setEGLDisplay(EGLDisplay display)
{
    this->display = display;
}

EGLDisplay GLWindow::getEGLDisplay() const
{
    return this->display;
}

void GLWindow::setEGLSurface(EGLSurface surface)
{
    this->surface = surface;
}

EGLSurface GLWindow::getEGLSurface() const
{
    return this->surface;
}

void GLWindow::setEGLContext(EGLContext context)
{
    this->context = context;
}

EGLContext GLWindow::getEGLContext() const
{
    return this->context;
}
}  // namespace qui

