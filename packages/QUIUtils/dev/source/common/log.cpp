// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIUtils.
//
//    QUIUtils is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIUtils is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIUtils.  If not, see <http://www.gnu.org/licenses/>.

#include <qui/log.h>
#include <time.h>
#ifdef PLATFORM_WIN32
#include <windows.h>
#endif
#ifdef PLATFORM_ANDROID
#include <android/log.h>
#endif
#include <iostream>
#include <fstream>
#include <cstring>

namespace qui
{
#ifdef BUILD_TYPE_DEBUG
int Log::ReportingLevel = LDEBUG;
#else
int Log::ReportingLevel = LDEBUG;
#endif

const char* toString(int level)
{
    switch (level)
    {
    default:
    case FATAL:     return "[FATAL] ";        break;
    case LERROR:    return "[ERROR] ";        break;
    case WARNING:   return "[WARNING] ";    break;
    case INFO:      return "";                break;
    case LDEBUG:    return "[DEBUG] ";        break;
    }
}

Log::Log()
{
    this->filename = "";
    this->line = -1;
}

Log::Log(const char* filename, int line)
{
    this->filename = (strrchr(filename, '/') + 1);
    this->line = line;
}

Log::~Log()
{
    os << std::endl << std::ends;
    if (msgLevel <= Log::ReportingLevel)
    {
#ifdef PLATFORM_ANDROID
        __android_log_print(ANDROID_LOG_DEBUG, "ro.qui.apps", os.str().c_str());
#else
        std::cout << os.str();
#endif
    }
}

std::ostringstream& Log::get(int level)
{
    os << toString(level);
#ifndef PLATFORM_WIN32
    if (filename != NULL && level != INFO)
    {
        os << filename << ":";
    }
    if (line != -1 && level != INFO)
    {
        os << line << " :\t";
    }
#endif
    msgLevel = level;
    return os;
}
}
