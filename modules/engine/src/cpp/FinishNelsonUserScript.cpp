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
#include "FinishNelsonUserScript.hpp"
#include "GetPreferencesPath.hpp"
#include "EvaluateScriptFile.hpp"
#include "Interface.hpp"
#include "CloseAllFiles.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    bool FinishNelsonUserScript(Evaluator* eval)
    {
        Context *ctx = eval->getContext();
        if (ctx)
        {
            std::wstring prefPath = GetPreferencesPath();
            boost::filesystem::path path(prefPath);
            path += L"/finish.nls";
            bool bIsFile = boost::filesystem::exists(path) && !boost::filesystem::is_directory(path);
            if (bIsFile)
            {
                std::wstring wstr = path.generic_wstring();
                try
                {
                    EvaluateScriptFile(eval, wstr.c_str());
                }
                catch (Exception &e)
                {
                    CloseAllFiles();
                    Interface *io = eval->getInterface();
                    e.what();
                    eval->setLastException(e);
                    std::wstring errmsg = _W("User finish.nls failed to run.");
                    if (io)
                    {
                        io->errorMessage(errmsg);
                    }
                    else
                    {
                        errmsg = errmsg + L"\n";
                        fwprintf(stderr, errmsg.c_str());
                    }
                }
                return true;
            }
            return false;
        }
        return false;
    }
    //=============================================================================
}
//=============================================================================
