// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIGameEntry.
//
//    QUIGameEntry is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIGameEntry is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIGameEntry.  If not, see <http://www.gnu.org/licenses/>.
#include <qui/StandardGameEntry.h>

namespace qui
{
StandardGameEntry::StandardGameEntry()
    : window(cpp0x::shared_ptr<GLWindow> (new GLWindow("", 0, 0)))
{
}

GLWindow& StandardGameEntry::getWindow() const
{
    return *window.get();
}

void StandardGameEntry::setWindow(GLWindow win)
{
    *this->window = win;
}
}  // namespace qui
