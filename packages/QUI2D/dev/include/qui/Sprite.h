// Copyright (C) 2013 Cristian Bidea
/** 
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
#ifndef PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SPRITE_H_
#define PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SPRITE_H_
#include <qui/IObject.h>
#include <GLES2/gl2.h>
#include <memory>

namespace qui
{
class GLTexture;
class GLVertexBufferObject;

namespace Q2D
{
struct ObjectData;

class Sprite : public IObject
{
 public:
    explicit Sprite(size_t materialId = 0xFFFFFFFF);
    ~Sprite();
    bool init();

    void paint();
    void setPosition(const glm::vec2& pos);
    void setAnchorPoint(const glm::vec2& anchor);
    bool getHasUpdate() const;
    void setHasUpdate(bool update);
    bool isVisible() const;
    void setVisible(bool visible);
    void update(uint64_t dt);
    glm::vec2& getPosition();
    void setRotationAngle(float angle);
    float getRotationAngle() const;
    glm::vec2& getAnchorPoint();
    void setMaterialId(size_t material);
    size_t getMaterialId() const;
 private:
    std::auto_ptr<qui::GLVertexBufferObject> vobj;
    GLuint matrixLoc;

    GLfloat* getVertices();
    GLushort* getIndices();
    std::auto_ptr<ObjectData> data;
};
}  // namespace 2D
}  // namespace qui
#endif  // PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_SPRITE_H_
