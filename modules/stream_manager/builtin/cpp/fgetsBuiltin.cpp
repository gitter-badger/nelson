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
#include "fgetsBuiltin.hpp"
#include "Error.hpp"
#include "FilesManager.hpp"
#include "File.hpp"
#include "FileGetLine.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector Nelson::StreamGateway::fgetsBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if ((argIn.size() < 0) || (argIn.size() > 2))
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (nLhs > 1)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    int nbCharacters = -1;
    if (argIn.size() == 2)
    {
        ArrayOf param2 = argIn[1];
        nbCharacters = (int)param2.getContentsAsDoubleScalar();
        if (nbCharacters >= 0)
        {
            if (std::isinf((double)nbCharacters))
            {
                nbCharacters = -1;
            }
        }
        else
        {
            Error(eval, _W("Second argument must be greater than zero."));
        }
    }
    ArrayOf param1 = argIn[0];
    if (param1.isDoubleType())
    {
        FilesManager *fm = (FilesManager *)(eval->FileManager);
        if (fm == nullptr)
        {
            Error(eval, _W("Problem with file manager."));
        }
        int32 iValue = (int32)param1.getContentsAsDoubleScalar();
        if (fm->isStdStream(iValue))
        {
            Error(eval, _W("Not implemented for requested file identifier."));
        }
        if (fm->isOpened(iValue))
        {
            File *f = fm->getFile(iValue);
            std::wstring result;
            if (FileGetLine(f, nbCharacters, true, result))
            {
                retval.push_back(ArrayOf::stringConstructor(result));
            }
            else
            {
                retval.push_back(ArrayOf::doubleConstructor(-1));
            }
        }
        else
        {
            Error(eval, _W("Invalid file identifier."));
        }
    }
    else
    {
        Error(eval, _W("Invalid file identifier."));
    }
    return retval;
}
//=============================================================================
