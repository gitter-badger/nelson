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
#include "systemBuiltin.hpp"
#include "Error.hpp"
#include "SystemCommand.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector Nelson::OsFunctionsGateway::systemBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    if (argIn.size() > 2)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (nLhs > 2)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    ArrayOfVector retval;
    bool bEcho = false;
    if (argIn.size() > 1)
    {
        if (argIn[1].isSingleString())
        {
            std::wstring flag = argIn[1].getContentsAsWideString();
            if (flag.compare(L"-echo") == 0)
            {
                bEcho = true;
            }
            else
            {
                Error(eval, _W("Unrecognized option. \"-echo\" expected."));
            }
        }
        else
        {
            Error(eval, ERROR_WRONG_ARGUMENT_2_TYPE_STRING_EXPECTED);
        }
    }
    if (argIn.size() == 0)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (nLhs == 0)
    {
        bEcho = true;
    }
    std::wstring cmd = L"";
    if (argIn[0].isSingleString())
    {
        cmd = argIn[0].getContentsAsWideString();
    }
    else
    {
        Error(eval, ERROR_WRONG_ARGUMENT_1_TYPE_STRING_EXPECTED);
    }
    int ierr = 0;
    ArrayOf ret = SystemCommand(cmd, ierr);
    if (bEcho)
    {
        Interface *io = eval->getInterface();
        std::wstring msg = ret.getContentsAsWideString();
        io->outputMessage(msg);
    }
    ArrayOf err = ArrayOf::doubleConstructor((double)ierr);
    retval.push_back(err);
    if (nLhs > 1)
    {
        retval.push_back(ret);
    }
    return retval;
}
//=============================================================================
