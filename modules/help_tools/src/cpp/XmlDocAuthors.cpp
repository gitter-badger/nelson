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
#include "XmlDocAuthors.hpp"
#include "XmlDocumentTags.hpp"
#include "characters_encoding.hpp"
#include "i18n.hpp"
#include "HtmlTags.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    XmlDocAuthors::XmlDocAuthors()
    {
        authorVector.clear();
    }
    //=============================================================================
    XmlDocAuthors::~XmlDocAuthors()
    {
        for (size_t k = 0; k < authorVector.size(); k++)
        {
            delete authorVector[k];
            authorVector[k] = nullptr;
        }
        authorVector.clear();
    }
    //=============================================================================
    void XmlDocAuthors::append(std::wstring value)
    {
        XmlDocAuthorItem *item = nullptr;
        try
        {
            item = new XmlDocAuthorItem(value);
        }
        catch (std::bad_alloc &e)
        {
            e;
            item = nullptr;
        }
        if (item)
        {
            authorVector.push_back(item);
        }
    }
    //=============================================================================
    std::wstring XmlDocAuthors::getItemType()
    {
        return utf8_to_wstring(AUTHORS_TAG);
    }
    //=============================================================================
    bool XmlDocAuthors::writeAsHtml(std::string &utf8stream)
    {
        if (authorVector.size() > 1)
        {
            utf8stream = utf8stream + HTML_H3_IN_TAG + _("Authors") + HTML_H3_OUT_TAG + "\n";
        }
        else
        {
            utf8stream = utf8stream + HTML_H3_IN_TAG + _("Author") + HTML_H3_OUT_TAG + "\n";
        }
        utf8stream = utf8stream + HTML_HR_OUT_TAG + "\n";
        utf8stream = utf8stream + "\n";
        for (size_t k = 0; k < authorVector.size(); k++)
        {
            authorVector[k]->writeAsHtml(utf8stream);
        }
        return true;
    }
    //=============================================================================
}
//=============================================================================
