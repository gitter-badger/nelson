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
#include "filepartsBuiltin.hpp"
#include "Error.hpp"
#include "FileParts.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector Nelson::FilesFoldersGateway::filepartsBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if ((argIn.size() == 1) || (argIn.size() == 2))
    {
        std::wstring wpath;
        std::wstring wtype;
        if (argIn.size() == 2)
        {
            if (nLhs > 1)
            {
                Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
            }
            if (argIn[1].isSingleString())
            {
                wtype = argIn[1].getContentsAsWideString();
                if (wtype.compare(L"path") == 0)
                {
                    // OK
                }
                else if (wtype.compare(L"filename") == 0)
                {
                    // OK
                }
                else if (wtype.compare(L"extension") == 0)
                {
                    // OK
                }
                else
                {
                    Error(eval, L"Argument #2 must contain a valid string 'path', 'filename' or 'extension' expected.");
                }
            }
            else
            {
                Error(eval, ERROR_WRONG_ARGUMENT_2_TYPE_STRING_EXPECTED);
            }
        }
        else
        {
            if (nLhs > 3)
            {
                Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
            }
        }
        if (argIn[0].isSingleString())
        {
            wpath = argIn[0].getContentsAsWideString();
        }
        else
        {
            Error(eval, ERROR_WRONG_ARGUMENT_1_TYPE_STRING_EXPECTED);
        }
        std::wstring respath;
        std::wstring resfilename;
        std::wstring resextension;
        FileParts(wpath, respath, resfilename, resextension);
        if (wtype.empty())
        {
            retval.push_back(ArrayOf::stringConstructor(respath));
            if (nLhs > 1)
            {
                retval.push_back(ArrayOf::stringConstructor(resfilename));
            }
            if (nLhs > 2)
            {
                retval.push_back(ArrayOf::stringConstructor(resextension));
            }
        }
        else
        {
            if (wtype.compare(L"path") == 0)
            {
                retval.push_back(ArrayOf::stringConstructor(respath));
            }
            else if (wtype.compare(L"filename") == 0)
            {
                retval.push_back(ArrayOf::stringConstructor(resfilename));
            }
            else if (wtype.compare(L"extension") == 0)
            {
                retval.push_back(ArrayOf::stringConstructor(resextension));
            }
        }
    }
    else
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    return retval;
}
//=============================================================================
