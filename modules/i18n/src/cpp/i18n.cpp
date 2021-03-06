//=============================================================================
// Copyright (c) 2016-2017 Allan CORNET (Nelson)
//=============================================================================
// LICENCE_BLOCK_BEGIN
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// LICENCE_BLOCK_END
//=============================================================================
#include <boost/locale.hpp>
#include "characters_encoding.hpp"
#include "i18n.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    std::wstring gettextw(std::wstring S)
    {
        return boost::locale::translate<wchar_t>(S.c_str());
    }
    //=============================================================================
    std::wstring gettextw(std::string S)
    {
        return utf8_to_wstring(boost::locale::translate(S).str());
    }
    //=============================================================================
    std::string gettext(std::string S)
    {
        return boost::locale::translate(S).str();
    }
    //=============================================================================
}
//=============================================================================
