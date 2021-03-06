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
#pragma once
//=============================================================================
#include <string>
#include <boost/container/vector.hpp>
#include "nlsHelp_tools_exports.h"
#include "XmlDocGenericItem.hpp"
#include "XmlDocSeeAlsoItem.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    class NLSHELP_TOOLS_IMPEXP XmlDocSeeAlso : public XmlDocGenericItem {
    private:
        boost::container::vector<XmlDocSeeAlsoItem *> seeAlsoVector;
    public:
        XmlDocSeeAlso();
        ~XmlDocSeeAlso();
        void append(std::wstring name, std::wstring link);
        std::wstring getItemType();
        bool writeAsHtml(std::string &utf8stream);
    };
    //=============================================================================
}
//=============================================================================
