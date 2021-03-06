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
#include "OverloadRequired.hpp"
#include "Error.hpp"
#include "ClassName.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    void OverloadRequired(Evaluator *eval, const ArrayOfVector& argIn, OVERLOAD_TYPE otype)
    {
        std::string functionName = eval->getCurrentFunctionName();
        std::string OverloadName("");
        switch (otype)
        {
            case Nelson::BINARY:
                OverloadName = ClassName(argIn[0]) + "_" + functionName + "_" + ClassName(argIn[1]);
                break;
            case Nelson::TRINARY:
                OverloadName = functionName + "_" + ClassName(argIn[0]) + "_" + ClassName(argIn[1]) + "_" + ClassName(argIn[2]);
                break;
            case Nelson::UNARY:
            case Nelson::FUNCTION:
                OverloadName = ClassName(argIn[0]) + "_" + functionName;
                break;
            default:
                Error(eval, _W("Wrong OVERLOAD_TYPE."));
                break;
        }
        Error(eval, _("function") + " " + OverloadName + " " + _("undefined."));
    }
    //=============================================================================
}
//=============================================================================