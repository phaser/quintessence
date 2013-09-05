/** 
 * @file SceneManager.h
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
#ifndef PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SCENEMANAGER_H_
#define PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SCENEMANAGER_H_
#include <qui/cpp11compat.h>
#include <stdint.h>
#include <vector>

namespace qui
{
class GLShader;
class Camera;
class StandardGameEntry;

namespace Q2D
{
class Scene;

class SceneManager
{
 public:
    explicit SceneManager(const qui::StandardGameEntry& game);
    ~SceneManager();
    void addScene(cpp0x::shared_ptr<Scene> scene);
    bool changeSceneTo(unsigned int scene);
    void update(uint64_t dt);
    void paint();
 private:
    cpp0x::shared_ptr<qui::Camera> camera;
    static std::vector<cpp0x::shared_ptr<Scene> > scenes;
    int currentScene;
};
}  // namespace 2D
}  // namespace qui
#endif  // PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SCENEMANAGER_H_
