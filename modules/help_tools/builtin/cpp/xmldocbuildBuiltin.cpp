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
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include "xmldocbuildBuiltin.hpp"
#include "Error.hpp"
#include "XmlDocDocument.hpp"
#include "characters_encoding.hpp"
#include "XmlDocDirectory.hpp"
#include "IsDirectory.hpp"
#include "XmlDocListOfDirectories.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
// xmldocbuild(source_dirs, destination_dir, main_title, export_format, overwrite)
ArrayOfVector Nelson::HelpToolsGateway::xmldocbuildBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (argIn.size() != 5)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (nLhs > 1)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    ArrayOf argSourceDirs = argIn[0];
    wstringVector listOfDirectories;
    if (argSourceDirs.isSingleString())
    {
        std::wstring dir = argSourceDirs.getContentsAsWideString();
        listOfDirectories.push_back(dir);
    }
    else if (argSourceDirs.isCell())
    {
        listOfDirectories = argSourceDirs.getContentAsWideStringVector(true);
    }
    else
    {
        Error(eval, ERROR_WRONG_ARGUMENT_1_TYPE_CELL_OF_STRINGS_EXPECTED);
    }
    for (size_t k = 0; k < listOfDirectories.size(); k++)
    {
        if (!IsDirectory(listOfDirectories[k]))
        {
            Error(eval, _W("Existing directory expected."));
        }
    }
    ArrayOf argDestinationDir = argIn[1];
    std::wstring dstDirectory = argDestinationDir.getContentsAsWideString();
    if (!IsDirectory(dstDirectory))
    {
        Error(eval, _W("Existing directory expected."));
    }
    ArrayOf argMainTitle = argIn[2];
    std::wstring mainTitle = argMainTitle.getContentsAsWideString();
    ArrayOf argExportFormat = argIn[3];
    std::wstring exportFormat = argExportFormat.getContentsAsWideString();
    if ((exportFormat != L"help") && (exportFormat != L"html"))
    {
        Error(eval, _W("format not supported: 'help' or 'html' expected."));
    }
    ArrayOf argOverwrite = argIn[4];
    logical forceOverwrite = argOverwrite.getContentAsLogicalScalar();
    bool isQtHelp = (exportFormat == L"help");
    XmlDocListOfDirectories xmlDirs(listOfDirectories, dstDirectory, mainTitle, forceOverwrite ? true : false, isQtHelp);
    if (xmlDirs.read())
    {
        std::wstring outputModuleName = xmlDirs.getOutputHelpBasename();
        try
        {
            xmlDirs.writeAsHtml();
        }
        catch (Exception &e)
        {
            Error(eval, e.getMessage());
        }
        retval.push_back(ArrayOf::stringConstructor(outputModuleName));
    }
    else
    {
        Error(eval, xmlDirs.getLastError());
    }
    return retval;
}
//=============================================================================
