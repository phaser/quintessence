/** 
 * @file SceneNode.cpp
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
#include <qui/SceneNode.h>
#include <qui/ShaderManager.h>
#include <qui/GLShader.h>
#include <GLES2/gl2.h>
#include <qui/ObjectData.h>
#include <vector>
#include <algorithm>

namespace qui
{
namespace Q2D
{
SceneNode::SceneNode()
    : IObject()
    , data(new ObjectData())
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::addChild(cpp0x::shared_ptr<IObject> child)
{
    this->children.push_back(child);
}

void SceneNode::removeChild(cpp0x::shared_ptr<IObject> child)
{
    this->children.erase(std::remove(this->children.begin(), this->children.end(), child), this->children.end());
}

void SceneNode::clearChildren()
{
    this->children.clear();
}
bool SceneNode::getHasUpdate() const
{
    return data->hasUpdate;
}

void SceneNode::setHasUpdate(bool update)
{
    data->hasUpdate = update;
}

bool SceneNode::isVisible() const
{
    return data->visible;
}

void SceneNode::setVisible(bool visible)
{
    data->visible = visible;
}

void SceneNode::setPosition(const glm::vec2& pos)
{
    data->setPosition(pos);
}

glm::vec2& SceneNode::getPosition()
{
    return data->position;
}

void SceneNode::setRotationAngle(float angle)
{
    data->setRotationAngle(angle);
}

float SceneNode::getRotationAngle() const
{
    return data->rotationAngle;
}

void SceneNode::setAnchorPoint(const glm::vec2& anchor)
{
    data->anchorPoint = anchor;
}

glm::vec2& SceneNode::getAnchorPoint()
{
    return data->anchorPoint;
}

void SceneNode::update(uint64_t dt)
{
    for (std::vector<cpp0x::shared_ptr<IObject> >::iterator it = children.begin()
       ; it != children.end()
       ; it++)
    {
        if ((*it)->getHasUpdate())
        {
            (*it)->update(dt);
        }
    }
}

void SceneNode::paint()
{
    for (std::vector<cpp0x::shared_ptr<IObject> >::iterator it = children.begin()
       ; it != children.end()
       ; it++)
    {
        if ((*it)->isVisible())
        {
            (*it)->paint();
        }
    }
}
}  // namespace Q2D
}  // namespace qui
