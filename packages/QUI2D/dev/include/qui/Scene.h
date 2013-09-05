/** 
 * @file Scene.h
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
#ifndef PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SCENE_H_
#define PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SCENE_H_

#include <qui/IObject.h>
#include <qui/cpp11compat.h>

namespace qui
{
namespace Q2D
{
class SceneManager;
class SceneNode;
class Scene : public IObject
{
 public:
    Scene();
    void addChild(cpp0x::shared_ptr<IObject> child);
    void removeChild(cpp0x::shared_ptr<IObject> child);
    void setSceneManager(qui::Q2D::SceneManager* sm);
    qui::Q2D::SceneManager& getSceneManager();

    bool getHasUpdate() const;
    void setHasUpdate(bool update);
    bool isVisible() const;
    void setVisible(bool visible);
    virtual void update(uint64_t dt);
    virtual void paint();
    void setPosition(const glm::vec2& pos);
    glm::vec2& getPosition();
    void setRotationAngle(float angle);
    float getRotationAngle() const;
    void setAnchorPoint(const glm::vec2& anchor);
    glm::vec2& getAnchorPoint();
    void setMaterialId(size_t /*material*/)
    {
    }
    size_t getMaterialId() const
    {
        return 0;
    }
 private:
    qui::Q2D::SceneManager* sceneManager;
    std::auto_ptr<qui::Q2D::SceneNode> sceneNode;
};
}  // namespace 2D
}  // namespace qui
#endif  // PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SCENE_H_
