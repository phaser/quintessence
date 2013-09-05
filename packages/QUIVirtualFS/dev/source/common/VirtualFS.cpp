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

#include <qui/VirtualFS.h>
#include <qui/log.h>
#include <qui/VirtualPathManager.h>
extern "C"
{
    #include <zip.h>
    #include <zipint.h>
}
#include <locale>
#include <algorithm>
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

namespace qui
{
/*========================================================================*
 * Local functions declaration
 *========================================================================*/
// trim from start
static inline std::string& ltrim(std::string &s)  // NOLINT
{
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string& rtrim(std::string &s)  // NOLINT
{
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string& trim(std::string &s)  // NOLINT
{
        return ltrim(rtrim(s));
}

/*========================================================================*
 * Public functions implementation
 *========================================================================*/
VirtualFS::VirtualFS()
{
}

VirtualFS::~VirtualFS()
{
}

/**
 * Checks if a file exists. If it is not an absolute path, it only
 * checks if it exists in the current directory.
 */
bool VirtualFS::fileExists(const std::string& path) const
{
    std::ifstream ifile(path.c_str());
    return ifile.is_open();
}

/**
 * If the path give is not absolute then it searches in all the
 * registered paths if the file exists and if it finds it, iterator
 * returns the whole path of the file.
 */
std::string VirtualFS::getRelativePath(std::string path, bool onlyDirs) const
{
    if (VirtualPathManager::GetInstance()->paths.size() <= 0)
    {
        return path;
    }
    path = trim(path);

    // If an absolute path don't do anything
    if (path.at(0) == '/'
        || path.at(1) == ':')
    {
        return path;
    }

    std::string newpath;
    // If any of the paths have already been prepended to this path, don't do anything
    for (std::map<std::string, RelativePathType>::iterator it = VirtualPathManager::GetInstance()->paths.begin()
         ; it != VirtualPathManager::GetInstance()->paths.end()
         ; it++)
    {
        newpath = it->first + "/";
        if (newpath.compare(path.substr(0, newpath.length())) == 0)
        {
            return path;
        }
    }

    // Return first existing file relative to a path
    for (std::map<std::string, RelativePathType>::iterator it = VirtualPathManager::GetInstance()->paths.begin()
         ; it != VirtualPathManager::GetInstance()->paths.end()
         ; it++)
    {
        std::ostringstream np;
        std::string p = it->first;
        np << p << "/" << path << '\0';
        if ((it->second == qui::DIRECTORY)
         && (fileExists(np.str()) == true))
        {
            if (onlyDirs)
            {
                return np.str();
            }
            else
            {
                return "DIR##" + np.str();
            }
        }
        else if (!onlyDirs
              && it->second == qui::ZIP
#ifdef PLATFORM_ANDROID
              && this->fileExistsInZip(p.c_str(), (path).c_str()) == true)
#else
              && this->fileExistsInZip(p.c_str(), path.c_str()) == true)
#endif
        {
            return "ZIP##" + p + "##" + path;
        }
    }
    return "";
}

/**
 * Adds a path to the relative paths array.
 */
void VirtualFS::addRelativePath(std::string path)
{
    for (std::map<std::string, RelativePathType>::iterator it = VirtualPathManager::GetInstance()->paths.begin()
         ; it != VirtualPathManager::GetInstance()->paths.end()
         ; it++)
    {
        if (path.compare(it->first) == 0)
        {
            return;
        }
    }

    if (path.substr(path.length()-4).compare(".zip") == 0
     || path.substr(path.length()-4).compare(".apk") == 0)
    {
        VirtualPathManager::GetInstance()->paths.insert(std::make_pair(path, qui::ZIP));
    }
    else
    {
        VirtualPathManager::GetInstance()->paths.insert(std::make_pair(path, qui::DIRECTORY));
    }
}

/**
 * Removes a path from the relative paths array.
 */
void VirtualFS::removeRelativePath(std::string path)
{
    for (std::map<std::string, RelativePathType>::iterator it = VirtualPathManager::GetInstance()->paths.begin()
         ; it != VirtualPathManager::GetInstance()->paths.end()
         ; it++)
    {
        if (path.compare(it->first) == 0)
        {
            VirtualPathManager::GetInstance()->paths.erase(it);
            return;
        }
    }
}

/**
 * Returns a null terminated char array that represents the contents of a file.
 */
cpp0x::shared_ptr<char> VirtualFS::getFileContentsAsText(const std::string& fileName)
{
    int length;
    cpp0x::shared_ptr<char> result = getFileContents(fileName, &length, 1);
    result.get()[length-1] = '\0';
    return result;
}

/**
 * It reads the contents of a file and returns it as an array of char.
 */
cpp0x::shared_ptr<char> VirtualFS::getFileContents(const std::string& fileName, int* len, const unsigned int pad)
{
    std::string path = this->getRelativePath(fileName, false);
    if (path.find("DIR##") != std::string::npos)
    {
        path = path.substr(5);
        return cpp0x::shared_ptr<char> (getFileContentsFromFile(path, len, pad), array_deleter<char>());
    }
    else if (path.find("ZIP##") != std::string::npos)
    {
        path = path.substr(5);
        return cpp0x::shared_ptr<char> (getFileContentsFromZip(path, len, pad), array_deleter<char>());
    }
    return cpp0x::shared_ptr<char> (getFileContentsFromFile(path, len, pad), array_deleter<char>());
}
/*========================================================================*
 * Private functions implementation
 *========================================================================*/
/**
 * Verifies if a given file exists inside a zip archive.
 */
bool VirtualFS::fileExistsInZip(const char *zip, const char *file) const
{
    struct zip *zfile = zip_open(zip, 0, NULL);
    if (zfile == NULL)
    {
        LOG(LERROR) << "Error on opening zip file: " << zip;
        return false;
    }
    zip_file* fileiz = 0;
    fileiz = zip_fopen(zfile, file, 0);
    if (fileiz == NULL)
    {
        LOG(WARNING) << "Couldn't open file -> " << file << " in zip -> " << zip << "!";
        return false;
    }
    zip_fclose(fileiz);
    zip_close(zfile);
    return true;
}

/**
 * Reads a file and returns its contents.
 */
char* VirtualFS::getFileContentsFromFile(const std::string& path, int* len, const unsigned int pad)
{
        std::ifstream ifs(path.c_str(), std::ifstream::in | std::ifstream::binary);
        if (!ifs.good())
        {
            LOG(LERROR) << "ifs.good() returned false!";
            return NULL;
        }
        size_t begin, end, length;
        begin = ifs.tellg();
        ifs.seekg(0, std::ios::end);
        end = ifs.tellg();
        length = end - begin;
        *len = length + pad;
        ifs.seekg(0, std::ios::beg);
        char* result = new char[*len];
        ifs.read(result, length);
        ifs.close();
        return result;
}

/**
 * Reads a file from a zip archive. The path given is of the form zip_file##file_inside_the_zip.
 */
char* VirtualFS::getFileContentsFromZip(const std::string& filename, int* len, const unsigned int pad)
{
    size_t pos = filename.find("##");
    if (pos == std::string::npos)
    {
        LOG(LERROR) << "Path is wrong! Should contain ## to separate zip file from file in zip!";
        return NULL;
    }
    std::string zip = filename.substr(0, pos);
    std::string file = filename.substr(pos+2);
    struct zip *zfile = zip_open(zip.c_str(), 0, NULL);
    if (zfile == NULL)
    {
        LOG(LERROR) << "Error on opening zip file: " << zip;
        return NULL;
    }
    struct zip_file* fileiz = 0;
    fileiz = zip_fopen(zfile, file.c_str(), 0);
    if (fileiz == NULL)
    {
        LOG(LERROR) << "Couldn't open file -> " << file << " in zip -> " << zip << "!";
        return NULL;
    }
    size_t size = fileiz->bytes_left;
    *len = size + pad;
    unsigned char* data = new unsigned char[*len];
    if (zip_fread(fileiz, data, size) == 0)
    {
        if (data)
        {
            delete [] data;
            data = NULL;
        }
        LOG(LERROR) << "Error reading from zip!";
    }
    zip_fclose(fileiz);
    zip_close(zfile);
    return reinterpret_cast<char*>(data);
}
}  // namespace qui
