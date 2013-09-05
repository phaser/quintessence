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

#include <TestGame.h>
#include <qui/ShaderManager.h>
#include <qui/log.h>
#include <qui/Hash.h>
#include <qui/IObject.h>
#include <ScreenManager.h>
#include <qui/OrthoCamera.h>
#include <anim/AnimatorsManager.h>
#include <string>

int positionLoc;
int texCoordLoc;

void glError()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG(LERROR) << "GL ERROR: " << error;
    }
}

std::auto_ptr<qui::StandardGameEntry> qui::game(new TestGame());

TestGame::TestGame()
{
    // _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG );
    qui::GLWindow lwin(std::string("My Application"), 1024, 768);
    this->setWindow(lwin);
}

TestGame::~TestGame()
{
}

void TestGame::init()
{
    LOG(INFO) << "TestGame::Init()";
    initializeCamera();
    game = cpp0x::shared_ptr<ScreenManager>(new ScreenManager(*this));
}

void TestGame::update(uint64_t dt)
{
    /* sceneManager->update(dt); */
    game->update(dt);
    anim::AnimatorsManager am;
    am.update(dt);
}

void TestGame::paint()
{
    // Set the viewport
    glViewport(0, 0, this->getWindow().getSize().x, this->getWindow().getSize().y);
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    /* sceneManager->paint(); */
    game->paint();
}

void TestGame::cleanup()
{
    LOG(INFO) << "TestGame::Cleanup()";
}


void TestGame::onSystemEvent(qui::SystemEvent event)
{
    switch (event)
    {
        case(qui::PAUSE):
        {
            break;
        }
        case(qui::RESUME):
        {
            break;
        }
        case(qui::WINDOW_RESIZED):
        {
            initializeCamera();
            break;
        }
    }
}


void TestGame::initializeCamera()
{
    camera = cpp0x::shared_ptr<qui::OrthoCamera>(
                                new qui::OrthoCamera(0
                                                   , getWindow().getSize().x
                                                   , 0
                                                   , getWindow().getSize().y
                                                   , 0
                                                   , 1));
    qui::Camera::setActiveCamera(camera.get());
}
