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
#include <boost/unordered_map.hpp>
#include <utility>
#include <string>
#include "Types.hpp"
#include "FunctionDef.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    class LocalFunctionsTable {
    private:
        boost::unordered_map<std::string, FuncPtr> cachedLocalMacro;
    public:
        LocalFunctionsTable();
        ~LocalFunctionsTable();
        bool find(const std::string key, FuncPtr& dest);
        bool add(const std::string key, const FuncPtr val);
    };
};
//=============================================================================
