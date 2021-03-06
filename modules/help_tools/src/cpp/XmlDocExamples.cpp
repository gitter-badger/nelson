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
#include "XmlDocExamples.hpp"
#include "XmlDocumentTags.hpp"
#include "characters_encoding.hpp"
#include "i18n.hpp"
#include "HtmlTags.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    XmlDocExamples::XmlDocExamples(bool isQtHelp)
    {
        this->bIsQtHelp = isQtHelp;
        examplesVector.clear();
    }
    //=============================================================================
    XmlDocExamples::~XmlDocExamples()
    {
        for (size_t k = 0; k < examplesVector.size(); k++)
        {
            delete examplesVector[k];
            examplesVector[k] = nullptr;
        }
        examplesVector.clear();
        this->bIsQtHelp = false;
    }
    //=============================================================================
    void XmlDocExamples::append(std::wstring type, std::wstring description, std::wstring data, std::wstring imageTag)
    {
        XmlDocExampleItem *item = nullptr;
        try
        {
            item = new XmlDocExampleItem(type, description, data, imageTag, this->bIsQtHelp);
        }
        catch (std::bad_alloc &e)
        {
            e;
            item = nullptr;
        }
        if (item)
        {
            examplesVector.push_back(item);
        }
    }
    //=============================================================================
    std::wstring XmlDocExamples::getItemType()
    {
        return utf8_to_wstring(EXAMPLES_TAG);
    }
    //=============================================================================
    bool XmlDocExamples::writeHeaderAsHtml(std::string &utf8stream)
    {
        utf8stream = utf8stream + "<link rel=\"stylesheet\" href=\"mono-blue.css\"  type=\"text/css\" />" + "\n";
        utf8stream = utf8stream + "<script src = \"highlight.pack.js\" type = \"text/javascript\">" + "\n" + HTML_SCRIPT_OUT_TAG + "\n";
        utf8stream = utf8stream + "<script type = \"text/javascript\">hljs.initHighlightingOnLoad();" + HTML_SCRIPT_OUT_TAG + "\n";
        utf8stream = utf8stream + HTML_SCRIPT_OUT_TAG + "\n";
        return true;
    }
    //=============================================================================
    bool XmlDocExamples::writeAsHtml(std::string &utf8stream)
    {
        if (examplesVector.size() > 1)
        {
            utf8stream = utf8stream + HTML_H3_IN_TAG + _("Examples") + HTML_H3_OUT_TAG + "\n";
        }
        else
        {
            utf8stream = utf8stream + HTML_H3_IN_TAG + _("Example") + HTML_H3_OUT_TAG + "\n";
        }
        utf8stream = utf8stream + HTML_HR_OUT_TAG + "\n";
        utf8stream = utf8stream + "\n";
        for (size_t k = 0; k < examplesVector.size(); k++)
        {
            examplesVector[k]->writeAsHtml(utf8stream);
        }
        utf8stream = utf8stream + "\n";
        return true;
    }
    //=============================================================================
    void XmlDocExamples::setDirectories(std::wstring srcDirectory, std::wstring dstDirectory)
    {
        for (size_t k = 0; k < examplesVector.size(); k++)
        {
            examplesVector[k]->setDirectories(srcDirectory, dstDirectory);
        }
    }
    //=============================================================================
}
//=============================================================================
