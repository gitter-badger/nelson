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
#include <boost/filesystem.hpp>
#include "ModulePath.hpp"
#include "ModulesHelpers.hpp"
#include "ModulesManager.hpp"
#include "Exception.hpp"
#include "FindDynamicLibraryName.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    std::wstring ModulePath(std::wstring moduleshortname)
    {
        std::wstring rpath = L"";
        return rpath;
    }
    //=============================================================================
    std::wstring ModulePath(std::wstring modulerootpath, std::wstring moduleshortname, MODULEPATH_OPTION option)
    {
        boost::filesystem::path p;
        switch (option)
        {
            case GET_BINARY_PATH:
            {
                p = ConstructBinariesPath(modulerootpath);
                p = p.generic_wstring();
                if (!boost::filesystem::is_directory(p))
                {
                    throw Exception(_W("Path does not exist:") + L"\n" + p.generic_wstring());
                }
            }
            break;
            case GET_ROOT_PATH:
            {
                p = ConstructRootName(modulerootpath, moduleshortname);
                p = p.generic_wstring();
                if (!boost::filesystem::is_directory(p))
                {
                    throw Exception(_W("Path does not exist:") + L"\n" + p.generic_wstring());
                }
            }
            break;
            case GET_ETC_PATH:
            {
                p = ConstructEtcName(modulerootpath, moduleshortname);
                p = p.generic_wstring();
                if (!boost::filesystem::is_directory(p))
                {
                    throw Exception(_W("Path does not exist:") + L"\n" + p.generic_wstring());
                }
            }
            break;
            case GET_DYNLIB_FULLPATH:
            {
                p = ConstructDynamicLibraryFullname(modulerootpath, moduleshortname);
                p = p.generic_wstring();
                std::wstring filename = FindDynamicLibraryName(p.parent_path().generic_wstring(), p.filename().generic_wstring(), false);
                if (filename.empty())
                {
                    throw Exception(_W("File does not exist:") + L"\n" + p.generic_wstring());
                }
            }
            break;
            case GET_SCRIPT_PATH:
            {
                p = ConstructScriptName(modulerootpath, moduleshortname);
                p = p.generic_wstring();
                if (!boost::filesystem::is_directory(p))
                {
                    throw Exception(_W("Path does not exist:") + L"\n" + p.generic_wstring());
                }
            }
            break;
            default:
            {
                throw Exception(_W("Wrong option."));
            }
            break;
        }
        return p.generic_wstring();
    }
    //=============================================================================
}
//=============================================================================
