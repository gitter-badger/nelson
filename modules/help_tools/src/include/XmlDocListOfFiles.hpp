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
#include "XmlDocDocument.hpp"
#include "Types.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    class NLSHELP_TOOLS_IMPEXP XmlDocListOfFiles {

    private:
        std::wstring chapterTitle;
        std::wstring chapterDescription;
        std::wstring moduleName;
        std::wstring lastError;
        wstringVector srcFiles;
        std::wstring dstDirectory;
        bool bOverwriteExistingFiles;
        boost::container::vector<XmlDocDocument *> xmlItems;
        void clearItems();
        std::wstring chapterResultFilename;
        bool isQtHelp;
        std::wstring sectionUpName;
        std::wstring sectionUpUrl;

    public:
        std::wstring getGeneratedChapterFilename();
        std::wstring getChapterTitle();
        std::wstring getModuleName();
        XmlDocListOfFiles(wstringVector srcFiles, std::wstring dstDirectory, bool bOverwriteExistingFiles = false, bool isQtHelp = false);
        ~XmlDocListOfFiles();
        bool read();
        bool writeAsHtml();
        std::wstring getLastError();
        void getIndex(wstringVector &names, wstringVector &urls, wstringVector &descriptions);
        void setUpSection(std::wstring sectionName, std::wstring sectionUrl);
    };
    //=============================================================================
}
//=============================================================================
