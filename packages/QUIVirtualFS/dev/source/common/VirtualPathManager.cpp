// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIVirtualFS.
//
//    QUIVirtualFS is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIVirtualFS is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIVirtualFS.  If not, see <http://www.gnu.org/licenses/>.

#include <qui/VirtualPathManager.h>

namespace qui
{
cpp0x::shared_ptr <VirtualPathManager> VirtualPathManager::singletonInstance
    = cpp0x::shared_ptr<VirtualPathManager> (new VirtualPathManager());

cpp0x::shared_ptr <VirtualPathManager> VirtualPathManager::GetInstance()
{
    return singletonInstance;
}
}  // namespace qui
