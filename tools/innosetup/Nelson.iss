;==============================================================================
; Copyright (c) 2016-2017 Allan CORNET (Nelson)
;==============================================================================
; LICENCE_BLOCK_BEGIN
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 2 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.
; LICENCE_BLOCK_END
;==============================================================================
#include "generated.iss"
;==============================================================================
#ifndef GENERATED_INFO
#define NELSON_X64
#define NELSON_DEBUG
#define CURRENT_YEAR "2017"
#define APPLICATION_VERSION "0.0.1.0"
#endif
#define APPLICATION_NAME "Nelson"
#define APPLICATION_EXE_GUI_NAME "Nelson-gui.exe"
#define APPLICATION_EXE_CLI_NAME "Nelson-cli.exe"
#define APPLICATION_EXE_ADV_CLI_NAME "Nelson-adv-cli.exe"
#define APPLICATION_PUBLISHER "Allan CORNET"
#ifdef NELSON_X64
#define FULL_APPLICATION_NAME APPLICATION_NAME + "-" + APPLICATION_VERSION + " (64 bits)"
#else
#define FULL_APPLICATION_NAME APPLICATION_NAME + "-" + APPLICATION_VERSION + " (32 bits)"
#endif
;==============================================================================
#define RootPath "../../"
#ifdef NELSON_X64
#define BinPath "x64"
#else
#define BinPath "win32"
#endif
;==============================================================================
[Setup]
#include "setup.iss"
;==============================================================================
[Languages]
#include "languages.iss"
;==============================================================================
[Tasks]
#include "tasks.iss"
;==============================================================================
[Files]
#include "files.iss"
;==============================================================================
[Icons]
#include "icons.iss"
;==============================================================================
[Run]
#include "run.iss"
;==============================================================================
[Code]
#include "code.iss"


