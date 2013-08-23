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

#ifndef PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_LOG_H_
#define PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_LOG_H_

#include <string>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <iostream>

#define LOG(level) \
    if (level > qui::Log::ReportingLevel) ; \
    else qui::Log(__FILE__, __LINE__).get(level)

#define FATAL   0
#define LERROR  1
#define WARNING 2
#define INFO    3
#define LDEBUG  4

namespace qui
{
/** A logger that logs to a device specific log.

    There are three types of logges that can be used.
    The only thing that differs between them is the prefix.

    Usage:
    \code
    LOG (LINFO) << "This is a normal string!";
    LOG (LWARNING) << "This is a warning string!";
    LOG (LERROR) << "This is an error string!";
    \endcode

    Outputs the following:
    \verbatim,
    This is a normal string!
    [*** WARNING ***] This is a warning string!
    [*** ERROR ***] This is an error string!
    \endverbatim
    \n See the \ref debug manual for more info.
*/
class Log
{
    public:
        Log();
        Log(const char* filename, int line);
        virtual ~Log();
        std::ostringstream& get(int level = INFO);

        static int ReportingLevel;
    private:
        std::ostringstream os;
        int msgLevel;
        const char* filename;
        int line;
        Log(const Log&);
        Log& operator= (const Log&);
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_LOG_H_

