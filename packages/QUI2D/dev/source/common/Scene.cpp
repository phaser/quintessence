/** 
 * @file Scene.cpp
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
#include <qui/Scene.h>
#include <qui/SceneManager.h>
#include <qui/SceneNode.h>

namespace qui
{
namespace Q2D
{
Scene::Scene()
    : sceneNode(new qui::Q2D::SceneNode())
{
}

void Scene::setSceneManager(qui::Q2D::SceneManager* sm)
{
    this->sceneManager = sm;
}

qui::Q2D::SceneManager& Scene::getSceneManager()
{
    return *this->sceneManager;
}

void Scene::addChild(cpp0x::shared_ptr<IObject> child)
{
    sceneNode->addChild(child);
}

void Scene::removeChild(cpp0x::shared_ptr<IObject> child)
{
    sceneNode->removeChild(child);
}

bool Scene::getHasUpdate() const
{
    return sceneNode->getHasUpdate();
}

void Scene::setHasUpdate(bool update)
{
    sceneNode->setHasUpdate(update);
}

bool Scene::isVisible() const
{
    return sceneNode->isVisible();
}

void Scene::setVisible(bool visible)
{
    sceneNode->setVisible(visible);
}

void Scene::setPosition(const glm::vec2& pos)
{
    sceneNode->setPosition(pos);
}

glm::vec2& Scene::getPosition()
{
    return sceneNode->getPosition();
}

void Scene::setRotationAngle(float angle)
{
    sceneNode->setRotationAngle(angle);
}

float Scene::getRotationAngle() const
{
    return sceneNode->getRotationAngle();
}

void Scene::setAnchorPoint(const glm::vec2& anchor)
{
    sceneNode->setAnchorPoint(anchor);
}

glm::vec2& Scene::getAnchorPoint()
{
    return sceneNode->getAnchorPoint();
}

void Scene::update(uint64_t dt)
{
    sceneNode->update(dt);
}

void Scene::paint()
{
    sceneNode->paint();
}
}  // namespace 2D
}  // namespace qui
