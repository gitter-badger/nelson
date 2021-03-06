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
#include "NelsonGateway.hpp"
#include "singleBuiltin.hpp"
#include "single_dispBuiltin.hpp"
#include "ndarraysingle_dispBuiltin.hpp"
#include "single_plus_singleBuiltin.hpp"
#include "single_minus_singleBuiltin.hpp"
#include "single_uminusBuiltin.hpp"
#include "single_vertcat_singleBuiltin.hpp"
#include "single_horzcat_singleBuiltin.hpp"
#include "ndarraysingle_horzcat_ndarraysingleBuiltin.hpp"
#include "ndarraysingle_vertcat_ndarraysingleBuiltin.hpp"
#include "ndarraysingle_isequalBuiltin.hpp"
#include "ndarraysingle_isequalnBuiltin.hpp"
#include "single_isequalBuiltin.hpp"
#include "single_isequalnBuiltin.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
const std::wstring gatewayName = L"single";
//=============================================================================
static const nlsGateway gateway[] =
{
    { "single", Nelson::SingleGateway::singleBuiltin, 1, 1 },
    { "single_disp", Nelson::SingleGateway::single_dispBuiltin, 0, 1 },
    { "ndarraysingle_disp", Nelson::SingleGateway::ndarraysingle_dispBuiltin, 0, 1 },
    { "single_plus_single", Nelson::SingleGateway::single_plus_singleBuiltin, 1, 1 },
    { "single_minus_single", Nelson::SingleGateway::single_minus_singleBuiltin, 1, 1 },
    { "single_uminus", Nelson::SingleGateway::single_uminusBuiltin, 1, 1 },
    { "single_horzcat_single", Nelson::SingleGateway::single_horzcat_singleBuiltin, 1, 2 },
    { "single_vertcat_single", Nelson::SingleGateway::single_vertcat_singleBuiltin, 1, 2 },
    { "ndarraysingle_horzcat_ndarraysingle", Nelson::SingleGateway::ndarraysingle_horzcat_ndarraysingleBuiltin, 1, 2 },
    { "ndarraysingle_vertcat_ndarraysingle", Nelson::SingleGateway::ndarraysingle_vertcat_ndarraysingleBuiltin, 1, 2 },
    { "ndarraysingle_isequal", Nelson::SingleGateway::ndarraysingle_isequalBuiltin, 1, 2 },
    { "ndarraysingle_isequaln", Nelson::SingleGateway::ndarraysingle_isequalnBuiltin, 1, 2 },
    { "single_isequal", Nelson::SingleGateway::single_isequalBuiltin, 1, 2 },
    { "single_isequaln", Nelson::SingleGateway::single_isequalnBuiltin, 1, 2 },

};
//=============================================================================
NLSGATEWAYFUNC(gateway)
//=============================================================================
NLSGATEWAYINFO(gateway)
//=============================================================================
NLSGATEWAYREMOVE(gateway)
//=============================================================================
NLSGATEWAYNAME()
//=============================================================================
