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
#include "isintegerBuiltin.hpp"
#include "Error.hpp"
#include "OverloadFunction.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector Nelson::TypeGateway::isintegerBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 1)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (argIn.size() != 1)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    bool bSuccess = false;
    retval = OverloadFunction(eval, nLhs, argIn, bSuccess);
    if (!bSuccess)
    {
        bool bRes = (argIn[0].getDataClass() == NLS_UINT8 ||
                     argIn[0].getDataClass() == NLS_INT8 ||
                     argIn[0].getDataClass() == NLS_UINT16 ||
                     argIn[0].getDataClass() == NLS_INT16 ||
                     argIn[0].getDataClass() == NLS_UINT32 ||
                     argIn[0].getDataClass() == NLS_INT32 ||
                     argIn[0].getDataClass() == NLS_UINT64 ||
                     argIn[0].getDataClass() == NLS_INT64);
        retval.push_back(ArrayOf::logicalConstructor(bRes));
    }
    return retval;
}
//=============================================================================
