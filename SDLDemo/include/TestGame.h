// Copyright (C) 2013 Cristian Bidea
// This file is part of TestGame.
//
//    TestGame is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    TestGame is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with TestGame.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TESTGAME_DEV_INCLUDE_TESTGAME_H_
#define TESTGAME_DEV_INCLUDE_TESTGAME_H_
#include <qui/StandardGameEntry.h>
#include <GLES2/gl2.h>
#include <qui/cpp11compat.h>
#include <qui/log.h>
#include <qui/OrthoCamera.h>
#include <stdint.h>
#include <qui/GLWindow.h>

namespace qui
{
    class GLShader;
    class Camera;
}
class ScreenManager;

class TestGame : public qui::StandardGameEntry
{
 public:
    TestGame();
    ~TestGame();
    void init();
    void update(uint64_t dt);
    void paint();
    void cleanup();
    void onSystemEvent(qui::SystemEvent event);
 private:
    cpp0x::shared_ptr<ScreenManager> game;
    cpp0x::shared_ptr<qui::Camera> camera;
    void initializeCamera();
};
#endif  // TESTGAME_DEV_INCLUDE_TESTGAME_H_
