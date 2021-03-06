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
Source: {#RootPath}bin\{#BinPath}\libnlsAssert_functions.dll; DestDir: {app}\bin\{#BinPath}\;
Source: {#RootPath}bin\{#BinPath}\libnlsAssert_functions_builtin.dll; DestDir: {app}\bin\{#BinPath}\;
;==============================================================================
Source: {#RootPath}modules\assert_functions\loader.nls; DestDir: {app}\modules\assert_functions\;
Source: {#RootPath}modules\assert_functions\etc\startup.nls; DestDir: {app}\modules\assert_functions\etc\;
Source: {#RootPath}modules\assert_functions\etc\finish.nls; DestDir: {app}\modules\assert_functions\etc\;
;==============================================================================
;Source: {#RootPath}modules\assert_functions\functions\*.nlf; DestDir: {app}\modules\assert_functions\functions\;
;==============================================================================
Source: {#RootPath}modules\assert_functions\help\*.qch; DestDir: {app}\modules\assert_functions\help\; Flags: recursesubdirs
;==============================================================================
Source: {#RootPath}modules\assert_functions\tests\*.nls; DestDir: {app}\modules\assert_functions\tests\; Flags: recursesubdirs
;==============================================================================
