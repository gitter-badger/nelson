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
#include <QtWidgets/QApplication>
#include <QtCore/QtGlobal>
#include "Evaluator.hpp"
#include "MainGuiObject.hpp"
#include "QtMainWindow.h"
#include "Console.hpp"
#include "GuiTerminal.hpp"
#include "GetQtPath.hpp"
#include "AddPathToEnvironmentVariable.hpp"
#include "Nelson_VERSION.h"
//===================================================================================
static QApplication *NelSonQtApp = nullptr;
static QtMainWindow* NelSonQtMainWindow = nullptr;
//===================================================================================
static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type)
    {
        case QtDebugMsg:
#if QT_VERSION > QT_VERSION_CHECK(5, 5, 0)
        case QtInfoMsg:
#endif
        case QtWarningMsg:
        case QtCriticalMsg:
        case QtFatalMsg:
        {
        }
        break;
    }
}
//===================================================================================
#if defined  _MSC_VER || defined __APPLE__
static char *argv[] = { "Nelson", Q_NULLPTR };
static int argc = sizeof(argv) / sizeof(char*) - 1;
#else
// These variables must be global for linux ...
static char *argv[] = { "Nelson", NULL };
static int argc = 1;
#endif
//===================================================================================
void InitGuiObjects(void)
{
    qInstallMessageHandler(myMessageOutput);
    if (NelSonQtApp == nullptr)
    {
        NelSonQtApp = new QApplication(argc, argv);
        QCoreApplication::setApplicationName("Nelson");
        QCoreApplication::setOrganizationDomain("https://nelson-numerical-software.github.io/nelson-website/");
        AddPathToEnvironmentVariable(std::wstring(L"PATH"), GetQtPath(L"BinariesPath"));
    }
}
//===================================================================================
void *CreateGuiEvaluator(void* vcontext, NELSON_ENGINE_MODE _mode)
{
    CreateConsole();
    NelSonQtMainWindow = new QtMainWindow();
    if (NelSonQtMainWindow)
    {
        GuiTerminal *nlsTerm = new GuiTerminal((void*)NelSonQtMainWindow);
        if (nlsTerm)
        {
            Evaluator *mainEvaluator = new Evaluator((Context*)vcontext, nlsTerm, _mode);
            if (mainEvaluator)
            {
                mainEvaluator->mainGuiObject = (void*)NelSonQtMainWindow;
            }
            return (void*)mainEvaluator;
        }
    }
    return nullptr;
}
//===================================================================================
void *CreateMainGuiObject(void)
{
    CreateConsole();
    NelSonQtMainWindow = new QtMainWindow();
    return (void*)NelSonQtMainWindow;
}
//===================================================================================
void DestroyMainGuiObject(void *term)
{
    if (NelSonQtApp)
    {
        if (NelSonQtMainWindow)
        {
            delete NelSonQtMainWindow;
            NelSonQtMainWindow = nullptr;
        }
        if (term)
        {
            GuiTerminal *nlsTerm = (GuiTerminal *)term;
            delete nlsTerm;
            nlsTerm = nullptr;
        }
        delete NelSonQtApp;
        NelSonQtApp = nullptr;
    }
    DestroyConsole();
}
//===================================================================================
void *GetMainGuiObject(void)
{
    return (void*)NelSonQtMainWindow;
}
//===================================================================================
