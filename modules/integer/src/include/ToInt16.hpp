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
    NLSINTEGER_IMPEXP ArrayOf ToInt16(ArrayOf a);
    NLSINTEGER_IMPEXP int16 ToInt16(int8 a);
    NLSINTEGER_IMPEXP int16 ToInt16(float a);
    NLSINTEGER_IMPEXP int16 ToInt16(double a);
    NLSINTEGER_IMPEXP int16 ToInt16(uint8 a);
    NLSINTEGER_IMPEXP int16 ToInt16(int16 a);
    NLSINTEGER_IMPEXP int16 ToInt16(uint16 a);
    NLSINTEGER_IMPEXP int16 ToInt16(int32 a);
    NLSINTEGER_IMPEXP int16 ToInt16(uint32 a);
    NLSINTEGER_IMPEXP int16 ToInt16(int64 a);
    NLSINTEGER_IMPEXP int16 ToInt16(uint64 a);

}
//=============================================================================
