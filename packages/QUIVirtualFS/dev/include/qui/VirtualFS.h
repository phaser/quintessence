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
#ifndef PACKAGES_QUI_QUIVIRTUALFS_DEV_INCLUDE_QUI_VIRTUALFS_H_
#define PACKAGES_QUI_QUIVIRTUALFS_DEV_INCLUDE_QUI_VIRTUALFS_H_
#include <qui/cpp11compat.h>
#include <string>
#include <iostream>
#include <istream>
#include <vector>

#define MAXPATHLENGTH 1024

namespace qui
{
    class VirtualFS
    {
    public:
        VirtualFS();
        ~VirtualFS();
        bool fileExists(const std::string& path) const;
        bool makeDirectory(const std::string& path, bool recursive = false) const;
        std::string getCurrentDirectory() const;
        void setCurrentDirectory(const std::string& path) const;
        std::string execute(const std::string& command, int* exitStatus) const;

        std::string getRelativePath(std::string path, bool onlyDirs = true) const;
        void addRelativePath(std::string path);
        void removeRelativePath(std::string path);

        cpp0x::shared_ptr<char> getFileContentsAsText(const std::string& fileName);
        cpp0x::shared_ptr<char> getFileContents(const std::string& fileName, int* len, const unsigned int pad = 0);
    private:
        std::string currentDir;

        bool fileExistsInZip(const char *zip, const char *file) const;
        char* getFileContentsFromFile(const std::string& filename, int* len, const unsigned int pad);
        char* getFileContentsFromZip(const std::string& filename, int* len, const unsigned int pad);
    };
}  // namespace qui
#endif  // PACKAGES_QUI_QUIVIRTUALFS_DEV_INCLUDE_QUI_VIRTUALFS_H_
