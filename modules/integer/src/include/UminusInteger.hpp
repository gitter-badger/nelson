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
#include "nlsInteger_exports.h"
#include "ArrayOf.hpp"
//=============================================================================
namespace Nelson {
    NLSINTEGER_IMPEXP ArrayOf integer_uminus(ArrayOf a);
    NLSINTEGER_IMPEXP int8 integer_uminus(int8 a);
    NLSINTEGER_IMPEXP int16 integer_uminus(int16 a);
    NLSINTEGER_IMPEXP int32 integer_uminus(int32 a);
    NLSINTEGER_IMPEXP int64 integer_uminus(int64 a);
    NLSINTEGER_IMPEXP uint8 integer_uminus(uint8 a);
    NLSINTEGER_IMPEXP uint16 integer_uminus(uint16 a);
    NLSINTEGER_IMPEXP uint32 integer_uminus(uint32 a);
    NLSINTEGER_IMPEXP uint64 integer_uminus(uint64 a);
}
//=============================================================================
