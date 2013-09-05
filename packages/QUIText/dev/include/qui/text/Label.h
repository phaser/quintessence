// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIText.
//
//    QUIText is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIText is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIText.  If not, see <http://www.gnu.org/licenses/>.
#ifndef PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_LABEL_H_
#define PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_LABEL_H_
#include <qui/IObject.h>
#include <qui/cpp11compat.h>
#include <GLES2/gl2.h>
#include <string>

namespace qui
{
class GLVertexBufferObject;

namespace Q2D
{
    struct ObjectData;
}  // namespace Q2D

namespace text
{
class Font;
class Label : public qui::Q2D::IObject
{
 public:
     static Label* getObject(const std::string& text
                           , size_t fontId);
     ~Label();

     void paint();
     void setPosition(const glm::vec2& pos);
     bool getHasUpdate() const;
     void setHasUpdate(bool update);
     bool isVisible() const;
     void setVisible(bool visible);
     void update(uint64_t dt);
     glm::vec2& getPosition();
     void setRotationAngle(float angle);
     float getRotationAngle() const;
     void setAnchorPoint(const glm::vec2& anchor);
     glm::vec2& getAnchorPoint();
     void setMaterialId(size_t material);
     size_t getMaterialId() const;
 protected:
     Label(const std::string& text
         , cpp0x::shared_ptr<Font> font);
     bool init();
 private:
    std::auto_ptr<qui::GLVertexBufferObject> vobj;
    std::auto_ptr<Q2D::ObjectData> data;
    std::string text;
    cpp0x::shared_ptr<Font> font;
    size_t xoffset;
    GLuint matrixLoc;
    glm::vec2 size;
    void realign(glm::vec2 oldAnchor);
};
}  // namespace text
}  // namespace qui
#endif  // PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_LABEL_H_
