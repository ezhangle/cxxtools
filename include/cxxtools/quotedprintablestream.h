/*
 * Copyright (C) 2007 Tommi Maekitalo
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CXXTOOLS_QUOTEDPRINTABLE_H
#define CXXTOOLS_QUOTEDPRINTABLE_H

#include <iostream>

namespace cxxtools
{

/**
   The QuotedPrintable_streambuf and QuotedPrintable_ostream implements a
   encoder for Quoted-printable encoding.

   Quoted-printable encoding is used sometimes in E-Mails to reduce the
   character set to 7 bit.

   Usage example:
   \code

      std::ostringstream s;
      cxxtools::QuotedPrintable_ostream q(s);
      q << "H\xe4tten H\xfcte ein \xdf im Namen, w\xe4ren sie m\xf6glicherweise keine H\xfcte mehr,\nsondern H\xfc\xdf" "e.";

      std::string quotedprintabletext = s.str();

   \endcode
 */
class QuotedPrintable_streambuf : public std::streambuf
{
    std::streambuf* sinksource;
    unsigned col;

  public:
    QuotedPrintable_streambuf(std::streambuf* sinksource_)
      : sinksource(sinksource_),
        col(0)
      { }

  protected:
    std::streambuf::int_type overflow(std::streambuf::int_type ch);
    std::streambuf::int_type underflow();
    int sync();
};

class QuotedPrintable_ostream : public std::ostream
{
    QuotedPrintable_streambuf streambuf;

  public:
    /// instantiate encode with a output-stream, which received encoded
    /// Data.
    QuotedPrintable_ostream(std::ostream& out)
      : std::ostream(0),
        streambuf(out.rdbuf())
      {
        init(&streambuf);
      }
    /// instantiate encode with a output-std::streambuf.
    QuotedPrintable_ostream(std::streambuf* sb)
      : std::ostream(0),
        streambuf(sb)
      {
        init(&streambuf);
      }
};

}

#endif // CXXTOOLS_QUOTEDPRINTABLE_H

