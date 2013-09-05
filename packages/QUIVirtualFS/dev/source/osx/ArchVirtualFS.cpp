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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string>

namespace qui
{
/**
 * The platform dependent (linux) way of creating a directory
 */
bool VirtualFS::makeDirectory(const std::string& path, bool recursive) const
{
    if (!recursive)
    {
        if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        {
            return false;
        }
    }
    return true;
}

/**
 * Returns the current working directory
 */
std::string VirtualFS::getCurrentDirectory() const
{
    char path[MAXPATHLENGTH];
    getcwd(path, MAXPATHLENGTH);
    return std::string(path);
}

/**
 * Changes the current working directory
 */
void VirtualFS::setCurrentDirectory(const std::string& path) const
{
    chdir(path.c_str());
}

/**
 * executes a command and returns it's output
 */
std::string VirtualFS::execute(const std::string& command, int* exitStatus) const
{
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
        {
            result += buffer;
        }
    }
    *exitStatus = pclose(pipe);
    return result;
}

}  // namespace qui

