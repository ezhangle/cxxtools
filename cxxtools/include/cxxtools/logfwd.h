/* cxxtools/logfwd.h
   Copyright (C) 2003 Tommi Maekitalo

This file is part of cxxtools.

Cxxtools is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Cxxtools is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with cxxtools; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330,
Boston, MA  02111-1307  USA
*/

#ifndef CXXTOOLS_LOGFWD_H
#define CXXTOOLS_LOGFWD_H

#include <cxxtools/config.h>

#ifdef CXXTOOLS_USE_LOG4CXX
////////////////////////////////////////////////////////////////////////
// log4cxx
//

#include <log4cxx/logger.h>

#define log_declare()  \
  extern log4cxx::LoggerPtr getLogger()
#define log_declare_class()  \
  static log4cxx::LoggerPtr getLogger()

#endif

#ifdef CXXTOOLS_USE_LOG4CPLUS

////////////////////////////////////////////////////////////////////////
// log4cplus
//
namespace log4cplus
{
  class Logger;
  Logger getLogger();
};

#define log_declare()   \
  extern log4cplus::Logger getLogger()
#define log_declare_class()   \
  static log4cplus::Logger getLogger()

#endif

#ifdef CXXTOOLS_USE_LOGSTDOUT
////////////////////////////////////////////////////////////////////////
// logging to stdout
//

#define log_declare()
#define log_declare_class()

#endif

#endif // CXXTOOLS_LOGFWD_H
