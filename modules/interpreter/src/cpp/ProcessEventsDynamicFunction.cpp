//=============================================================================
#include <string>
#include <stdlib.h>
#include "ProcessEventsDynamicFunction.hpp"
#include "dynamic_library.hpp"
//=============================================================================
static Nelson::library_handle nlsGuiHandleDynamicLibrary = nullptr;
static bool bFirstDynamicLibraryCall = true;
//=============================================================================
static void initGuiDynamicLibrary(void)
{
    if (bFirstDynamicLibraryCall)
    {
        std::string fullpathGuiSharedLibrary = "libnlsGui" + Nelson::get_dynamic_library_extension();
#ifdef _MSC_VER
        char *buf = new char[MAX_PATH];
        if (buf)
        {
            DWORD dwRet = ::GetEnvironmentVariableA("NELSON_BINARY_PATH", buf, MAX_PATH);
            if (dwRet)
            {
                fullpathGuiSharedLibrary = std::string(buf) + std::string("/") + fullpathGuiSharedLibrary;
            }
            delete[] buf;
        }
#else
        char const* tmp = getenv("NELSON_BINARY_PATH");
        if (tmp != nullptr)
        {
            fullpathGuiSharedLibrary = std::string(tmp) + std::string("/") + fullpathGuiSharedLibrary;
        }
#endif
        nlsGuiHandleDynamicLibrary = Nelson::load_dynamic_library(fullpathGuiSharedLibrary.c_str());
        if (nlsGuiHandleDynamicLibrary)
        {
            bFirstDynamicLibraryCall = false;
        }
    }
}
//=============================================================================
void ProcessEventsDynamicFunction(bool bWait)
{
    typedef void (*PROC_ProcessEvents) (bool);
    static PROC_ProcessEvents ProcessEventsPtr = nullptr;
    initGuiDynamicLibrary();
    if (!ProcessEventsPtr)
    {
        ProcessEventsPtr = reinterpret_cast<PROC_ProcessEvents>(Nelson::get_function(nlsGuiHandleDynamicLibrary, "NelSonProcessEvents"));
    }
    if (ProcessEventsPtr)
    {
        ProcessEventsPtr(bWait);
    }
}
//=============================================================================
