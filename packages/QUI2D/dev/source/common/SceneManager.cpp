/** 
 * @file SceneManager.cpp
 * @author Cristian Bidea
 * @copyright 2012 Cristian Bidea
 *
 * This file is part of QUI2D.
 *
 *    QUI2D is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published
 *    by the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    QUI2D is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with QUI2D.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <qui/SceneManager.h>
#include <qui/GLShader.h>
#include <qui/Scene.h>
#include <qui/OrthoCamera.h>
#include <qui/StandardGameEntry.h>
#include <qui/ShaderManager.h>
#include <vector>

namespace qui
{
namespace Q2D
{
std::vector<cpp0x::shared_ptr<Scene> > SceneManager::scenes;

SceneManager::SceneManager(const qui::StandardGameEntry& game)
    : currentScene(-1)
{
    camera = cpp0x::shared_ptr<qui::OrthoCamera>(
                                new qui::OrthoCamera(0
                                                   , game.getWindow().getSize().x
                                                   , 0
                                                   , game.getWindow().getSize().y
                                                   , 0
                                                   , 1));
    Camera::setActiveCamera(camera.get());
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(cpp0x::shared_ptr<Scene> scene)
{
    scene->setSceneManager(this);
    scenes.push_back(scene);
}

bool SceneManager::changeSceneTo(unsigned int scene)
{
    currentScene = scene;
    return true;
}

void SceneManager::update(uint64_t dt)
{
    if (currentScene == -1)
    {
        return;
    }
    scenes[currentScene]->update(dt);
}

void SceneManager::paint()
{
    if (currentScene == -1)
    {
        return;
    }

    Camera::setActiveCamera(camera.get());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    scenes[currentScene]->paint();
}
}  // namespace 2D
}  // namespace qui
