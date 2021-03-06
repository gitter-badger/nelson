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
#include "assert_isfalseBuiltin.hpp"
#include "Error.hpp"
#include "Assert_IsFalse.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector Nelson::AssertFunctionsGateway::assert_isfalseBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (argIn.size() == 0 || argIn.size() > 2)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (nLhs > 2)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    std::wstring modifiedmsg = L"";
    if (argIn.size() == 2)
    {
        ArrayOf param2 = argIn[1];
        modifiedmsg = param2.getContentsAsWideString();
    }
    ArrayOf param1 = argIn[0];
    if (!param1.isLogical())
    {
        Error(eval, ERROR_WRONG_ARGUMENT_1_TYPE_LOGICAL_EXPECTED);
    }
    if (!param1.isScalar())
    {
        Error(eval, ERROR_SIZE_SCALAR_EXPECTED);
    }
    logical res = param1.getContentAsLogicalScalar();
    std::wstring msg = L"";
    res = Assert_IsFalse(res, modifiedmsg, msg);
    if (nLhs == 0)
    {
        if (res == 0)
        {
            Error(eval, msg);
        }
    }
    else
    {
        retval.push_back(ArrayOf::logicalConstructor(res == 0 ? false : true));
        if (nLhs > 1)
        {
            retval.push_back(ArrayOf::stringConstructor(msg));
        }
    }
    return retval;
}
//=============================================================================
