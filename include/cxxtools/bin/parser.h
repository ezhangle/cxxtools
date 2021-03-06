/*
 * Copyright (C) 2011 Tommi Maekitalo
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

#ifndef CXXTOOLS_BIN_PARSER_H
#define CXXTOOLS_BIN_PARSER_H

#include <cxxtools/serializationinfo.h>
#include <vector>

namespace cxxtools
{

namespace bin
{

class Deserializer;

class Parser
{
        Parser(const Parser&) { }
        Parser& operator= (const Parser&) { return *this; }

        explicit Parser(std::vector<std::string>* dictionary)
            : _next(0),
              _dictionary(dictionary)
        { }

    public:
        Parser()
            : _next(0),
              _dictionary(&_mydictionary)
        { }

        ~Parser() 
        {
            delete _next;
        }

        void begin(Deserializer& handler);

        void skip();

        bool advance(char ch); // returns true, if number is read completely

    private:

        bool processFloatBase(char ch, unsigned shift, unsigned expOffset);
        void dict(const std::string& s);

        enum State
        {
            state_type,
            state_name,
            state_name_idx0,
            state_name_idx1,
            state_value_type_other,
            state_value_type_other_idx0,
            state_value_type_other_idx1,
            state_value_intsign,
            state_value_int,
            state_value_uint,
            state_value_bool,
            state_value_bcd0,
            state_value_bcd,
            state_value_binary_length,
            state_value_binary,
            state_value_value,
            state_sfloat_exp,
            state_sfloat_base,
            state_mfloat_exp,
            state_mfloat_base,
            state_lfloat_exp,
            state_lfloat_base,
            state_object_type,
            state_object_type_other,
            state_object_type_other_idx0,
            state_object_type_other_idx1,
            state_object_member,
            state_object_member_value,
            state_array_type,
            state_array_type_other,
            state_array_type_other_idx0,
            state_array_type_other_idx1,
            state_array_member,
            state_array_member_value,
            state_array_member_value_next,
            state_end
        } _state, _nextstate;

        std::string _token;
        unsigned _count;
        uint64_t _int;
        int _exp;
        bool _isNeg;
        unsigned _dictidx;
        Deserializer* _deserializer;
        Parser* _next;
        std::vector<std::string> _mydictionary;
        std::vector<std::string>* _dictionary;
};
}
}

#endif // CXXTOOLS_BIN_PARSER_H

