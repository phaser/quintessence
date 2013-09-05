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
#ifndef PACKAGES_QUI_QUIGAMEENTRY_DEV_INCLUDE_QUI_GLWINDOW_H_
#define PACKAGES_QUI_QUIGAMEENTRY_DEV_INCLUDE_QUI_GLWINDOW_H_
#include <glm/glm.hpp>
#include <string>

typedef void *EGLContext;
typedef void *EGLDisplay;
typedef void *EGLSurface;

namespace qui
{
class GLWindow
{
 public:
    GLWindow(std::string name, int width, int height);
    ~GLWindow();
    GLWindow& operator=(const GLWindow& win);
    inline void setSize(const glm::vec2& size)
    {
        this->size = size;
    }
    inline glm::vec2 getSize()
    {
        return this->size;
    }
    inline const std::string& getWindowName() const
    {
        return windowName;
    }

    void setEGLDisplay(EGLDisplay display);
    EGLDisplay getEGLDisplay() const;
    void setEGLSurface(EGLSurface surface);
    EGLSurface getEGLSurface() const;
    void setEGLContext(EGLContext context);
    EGLContext getEGLContext() const;
 private:
    std::string windowName;
    glm::vec2 size;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIGAMEENTRY_DEV_INCLUDE_QUI_GLWINDOW_H_
