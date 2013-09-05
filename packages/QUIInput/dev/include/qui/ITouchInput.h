// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIInput.
//
//    QUIInput is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIInput is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIInput.  If not, see <http://www.gnu.org/licenses/>.
#ifndef PACKAGES_QUI_QUIINPUT_DEV_INCLUDE_QUI_ITOUCHINPUT_H_
#define PACKAGES_QUI_QUIINPUT_DEV_INCLUDE_QUI_ITOUCHINPUT_H_
#include <list>
namespace qui
{
namespace input
{
class TouchInputEvent;
class ITouchInput
{
 public:
     virtual ~ITouchInput()
     {
     }
     virtual void onTouchesBegan(std::list<TouchInputEvent*> touches) =0;
     virtual void onTouchesMoved(std::list<TouchInputEvent*> touches) =0;
     virtual void onTouchesEnd(std::list<TouchInputEvent*> touches) =0;
     virtual void onTouchesCanceled(std::list<TouchInputEvent*> touches) =0;
     virtual bool canReceiveUpdates() =0;
};
}  // namespace input
}  // namespace qui
#endif  // PACKAGES_QUI_QUIINPUT_DEV_INCLUDE_QUI_ITOUCHINPUT_H_
