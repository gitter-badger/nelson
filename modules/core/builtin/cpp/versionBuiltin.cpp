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
#include "versionBuiltin.hpp"
#include "Error.hpp"
#include "Nelson_VERSION.h"
#include "ToCellString.hpp"
#include "VersionCompilerFlags.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector Nelson::CoreGateway::versionBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (argIn.size() == 0)
    {
        if (nLhs > 2)
        {
            Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
        }
        std::string version;
        version.append(NELSON_VERSION_STRING);
        version.append(" (");
        version.append(NELSON_RELEASE_NAME);
        version.append(")");
        retval.push_back(ArrayOf::stringConstructor(version));
        if (nLhs > 1)
        {
            retval.push_back(ArrayOf::stringConstructor(__DATE__));
        }
    }
    else if (argIn.size() == 1)
    {
        if (nLhs > 1)
        {
            Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
        }
        std::wstring option;
        if (argIn[0].isSingleString())
        {
            option = argIn[0].getContentsAsWideString();
        }
        else
        {
            Error(eval, ERROR_WRONG_ARGUMENT_1_TYPE_STRING_EXPECTED);
        }
        if (option.compare(L"-date") == 0)
        {
            retval.push_back(ArrayOf::stringConstructor(__TIMESTAMP__));
        }
        else if(option.compare(L"-description") == 0)
        {
            retval.push_back(ArrayOf::stringConstructor(L""));
        }
        else if (option.compare(L"-release") == 0)
        {
            retval.push_back(ArrayOf::stringConstructor(NELSON_RELEASE_NAME));
        }
        else if (option.compare(L"-compiler") == 0)
        {
            retval.push_back(ToCellStringAsRow(VersionCompilerFlags()));
        }
        else if (option.compare(L"-commit_hash") == 0)
        {
            retval.push_back(ArrayOf::stringConstructor(NELSON_VERSION_COMMIT_HASH));
        }
        else if (option.compare(L"-number") == 0)
        {
            ArrayOf vectRes = ArrayOf::doubleVectorConstructor(4);
            double *vectAsDouble = (double*)vectRes.getReadWriteDataPointer();
            if (vectAsDouble)
            {
                vectAsDouble[0] = NELSON_VERSION_MAJOR;
                vectAsDouble[1] = NELSON_VERSION_MINOR;
                vectAsDouble[2] = NELSON_VERSION_MAINTENANCE;
                vectAsDouble[3] = NELSON_VERSION_BUILD;
            }
            retval.push_back(vectRes);
        }
        else
        {
            Error(eval, _W("Unknow option."));
        }
    }
    else
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    return retval;
}
//=============================================================================
