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
#include "ModulesHelpers.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    std::wstring ConstructBinariesPath(std::wstring modulerootpath)
    {
        std::wstring binariespath;
#ifdef _MSC_VER
#ifdef _WIN64
        binariespath = modulerootpath + std::wstring(L"/bin/x64");
#else
        binariespath = modulerootpath + std::wstring(L"/bin/win32");
#endif
#else
#ifdef __APPLE__
#ifdef __x86_64__
        binariespath = modulerootpath + std::wstring(L"/bin/macosx64");
#else
        binariespath = modulerootpath + std::wstring(L"/bin/macosx32");
#endif
#else
#ifdef __x86_64__
        binariespath = modulerootpath + std::wstring(L"/bin/linux64");
#else
        binariespath = modulerootpath + std::wstring(L"/bin/linux32");
#endif
#endif
#endif
        return binariespath;
    }
    //=============================================================================
    std::wstring ConstructDynamicLibraryName(std::wstring moduleshortname)
    {
        std::wstring libname = std::wstring(L"libnls") + moduleshortname + std::wstring(L"_builtin");
#ifdef _MSC_VER
        libname = libname + std::wstring(L".dll");
#else
#ifdef __APPLE__
        libname = libname + std::wstring(L".dylib");
#else
        libname = libname + std::wstring(L".so");
#endif
#endif
        return libname;
    }
    //=============================================================================
    std::wstring ConstructEtcName(std::wstring modulerootpath, std::wstring moduleshortname)
    {
        std::wstring etcpath;
        if (moduleshortname.empty())
        {
            etcpath = modulerootpath + L"/etc";
        }
        else
        {
            etcpath = modulerootpath + L"/modules/" + moduleshortname + L"/etc";
        }
        return etcpath;
    }
    //=============================================================================
    std::wstring ConstructRootName(std::wstring modulerootpath, std::wstring moduleshortname)
    {
        std::wstring rootpath;
        if (moduleshortname.empty())
        {
            rootpath = modulerootpath + L"/";
        }
        else
        {
            rootpath = modulerootpath + L"/modules/" + moduleshortname + L"/";
        }
        return rootpath;
    }
    //=============================================================================
    std::wstring ConstructScriptName(std::wstring modulerootpath, std::wstring moduleshortname)
    {
        std::wstring scriptspath;
        if (moduleshortname.empty())
        {
            scriptspath = modulerootpath + L"/functions";
        }
        else
        {
            scriptspath = modulerootpath + L"/modules/" + moduleshortname + L"/functions";
        }
        return scriptspath;
    }
    //=============================================================================
    std::wstring ConstructDynamicLibraryFullname(std::wstring modulerootpath, std::wstring moduleshortname)
    {
        return ConstructBinariesPath(modulerootpath) + L"/" + ConstructDynamicLibraryName(moduleshortname);
    }
}
//=============================================================================
