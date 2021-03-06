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
#include "varlockBuiltin.hpp"
#include "LockVariable.hpp"
#include "IsValidVariableName.hpp"
#include "Error.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector Nelson::MemoryGateway::varlockBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs != 0)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (argIn.size() != 2)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (!argIn[0].isSingleString())
    {
        Error(eval, ERROR_WRONG_ARGUMENT_1_TYPE_STRING_EXPECTED);
    }
    std::string scopename = argIn[0].getContentsAsCString();
    if (!((scopename.compare("global") == 0) || (scopename.compare("base") == 0) || (scopename.compare("caller") == 0) || (scopename.compare("local") == 0)))
    {
        Error(eval, _W("#1 Argument must contain a string: \'global\', \'base\', \'local\' or \'caller\' expected."));
    }
    Context *context = eval->getContext();
    Scope * scope = nullptr;
    if (scopename.compare("global") == 0)
    {
        scope = context->getGlobalScope();
    }
    if (scopename.compare("base") == 0)
    {
        scope = context->getBaseScope();
    }
    if (scopename.compare("caller") == 0)
    {
        scope = context->getCallerScope();
    }
    if (scopename.compare("local") == 0)
    {
        scope = context->getCurrentScope();
    }
    if (!argIn[1].isSingleString())
    {
        Error(eval, ERROR_WRONG_ARGUMENT_2_TYPE_STRING_EXPECTED);
    }
    std::string varname = argIn[1].getContentsAsCString();
    if (!IsValidVariableName(varname))
    {
        Error(eval, _W("#2 Argument must contain a valid variable name."));
    }
    if (!scope->isVariable(varname))
    {
        Error(eval, _W("#2 Argument must be an existing variable name."));
    }
    LockVariable(varname, scope);
    return retval;
}
//=============================================================================
