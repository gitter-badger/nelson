#==============================================================================
# Copyright (c) 2016-2017 Allan CORNET (Nelson)
#==============================================================================
# LICENCE_BLOCK_BEGIN
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# LICENCE_BLOCK_END
#==============================================================================
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
#============================================================================== 
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}")
#============================================================================== 
set (Nelson_VERSION_MAJOR_DEFAULT 0)
set (Nelson_VERSION_MINOR_DEFAULT 1)
set (Nelson_VERSION_MAINTENANCE_DEFAULT 4)
#============================================================================== 
if(DEFINED ENV{NELSON_VERSION_MAJOR})
  set (Nelson_VERSION_MAJOR $ENV{NELSON_VERSION_MAJOR})
else()
  set (Nelson_VERSION_MAJOR ${Nelson_VERSION_MAJOR_DEFAULT})
endif()
#============================================================================== 
if(DEFINED ENV{Nelson_VERSION_MINOR})
  set (Nelson_VERSION_MINOR $ENV{Nelson_VERSION_MINOR})
else()
  set (Nelson_VERSION_MINOR ${Nelson_VERSION_MINOR_DEFAULT})
endif()
#============================================================================== 
if(DEFINED ENV{NELSON_VERSION_MAINTENANCE})
  set (Nelson_VERSION_MAINTENANCE $ENV{NELSON_VERSION_MAINTENANCE})
else()
  set (Nelson_VERSION_MAINTENANCE ${Nelson_VERSION_MAINTENANCE_DEFAULT})
endif()
#============================================================================== 
if(DEFINED ENV{NELSON_VERSION_BUILD})
  set (Nelson_VERSION_BUILD $ENV{NELSON_VERSION_BUILD})
else()
  string(TIMESTAMP Nelson_VERSION_BUILD "%Y%m%d%H%M%S")
endif()
#============================================================================== 
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/")
SET(BUILD_SHARED_LIBS "true")
#============================================================================== 
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  message( SEND_ERROR "On Windows, please uses Visual studio solution." )
ENDIF()
#============================================================================== 
IF (EXISTS ${CMAKE_SOURCE_DIR}/modules/core/src/include/Nelson_VERSION.h)
ELSE()
configure_file (
  "${CMAKE_SOURCE_DIR}/modules/core/src/include/Nelson_VERSION.h.in"
  "${CMAKE_SOURCE_DIR}/modules/core/src/include/Nelson_VERSION.h"
  )
ENDIF()
#============================================================================== 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_STANDARD 11)
else()
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
#============================================================================== 
CHECK_CXX_COMPILER_FLAG("-fPIC" COMPILER_SUPPORTS_FPIC)
if (COMPILER_SUPPORTS_FPIC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
#============================================================================== 
include(CheckSymbolExists)
check_symbol_exists("fseek64" "stdio.h" HAVE_FSEEK64)
check_symbol_exists("ftell64" "stdio.h" HAVE_FTELL64) 
#==============================================================================
SET(CMAKE_INSTALL_RPATH ".")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set (CMAKE_MACOSX_RPATH 1)
ENDIF()
#============================================================================== 
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(BITNESS 32)
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
      SET(BITNESS 64)
      add_definitions(-D_LARGEFILE_SOURCE)
      add_definitions(-D_FILE_OFFSET_BITS=64)
    ENDIF()
ENDIF()
#==============================================================================
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  get_filename_component(MYEIGEN ${CMAKE_SOURCE_DIR}/../Nelson-thirdparty-linux${BITNESS}/Eigen ABSOLUTE) 
ENDIF()
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  get_filename_component(MYEIGEN ${CMAKE_SOURCE_DIR}/../Nelson-thirdparty-macosx/Eigen ABSOLUTE)
ENDIF()  
IF (EXISTS ${MYEIGEN})
  set(EIGEN3_INCLUDE_DIR ${MYEIGEN})
ELSE()
  FIND_PACKAGE(Eigen3 3.3 REQUIRED)
ENDIF()
#==============================================================================
IF(DEFINED ENV{QTDIR})
  SET(QTDIR $ENV{QTDIR})
ELSE()
  IF (EXISTS $ENV{HOME}/Qt5.6.0/5.6/clang_64)
    SET(QTDIR $ENV{HOME}/Qt5.6.0/5.6/clang_64)
  ENDIF()
  IF (EXISTS $ENV{HOME}/Qt/5.7/clang_64)
    SET(QTDIR $ENV{HOME}/Qt/5.7/clang_64)
  ENDIF()
  IF (EXISTS $ENV{HOME}/Qt/5.8/clang_64)
    SET(QTDIR $ENV{HOME}/Qt/5.8/clang_64)
  ENDIF()
ENDIF()
SET(CMAKE_PREFIX_PATH ${QTDIR})
IF(DEFINED ENV{QTDIR_BINARIES})
ELSE()
  IF (EXISTS ${QTDIR}/bin)
    set(ENV{QTDIR_BINARIES} ${QTDIR}/bin )
    set(QTDIR_BINARIES ${QTDIR}/bin )
  ELSE()  
    message(WARNING "Please define QTDIR_BINARIES environment variable." )
  ENDIF()
ENDIF()
#==============================================================================
FIND_PACKAGE(LAPACK REQUIRED)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
FIND_PACKAGE(LAPACKE REQUIRED)
ENDIF()
FIND_PACKAGE(PkgConfig REQUIRED)
FIND_PACKAGE(libffi REQUIRED)
FIND_PACKAGE(Boost 1.60.0 COMPONENTS system filesystem locale thread chrono regex date_time REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5PrintSupport REQUIRED)
FIND_PACKAGE(LibXml2 REQUIRED)
FIND_PACKAGE(icu REQUIRED)
#============================================================================== 
add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_ALL_DYN_LINK)
#============================================================================== 
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(BIN_DIRECTORY ${PROJECT_BINARY_DIR}/bin/linux${BITNESS})
ENDIF()
#==============================================================================
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(BIN_DIRECTORY ${PROJECT_BINARY_DIR}/bin/macosx64)
  set(CMAKE_OSX_ARCHITECTURES "x86_64")
  set(Boost_NO_SYSTEM_PATHS "TRUE")
  set(MAC_FRAMEWORK_FOUNDATION_LIBRARY "-framework Foundation")
  IF(EXISTS "/usr/local/lib/liblapacke.a")
    LINK_DIRECTORIES(/usr/local/lib)
    set(MAC_LAPACKE_LIBRARY -lblas -llapack -llapacke)
  ELSE()
    get_filename_component(LAPACKE_LIB ${CMAKE_SOURCE_DIR}/../Nelson-thirdparty-macosx/LAPACKE/sierra/lib ABSOLUTE)
    IF (EXISTS ${LAPACKE_LIB})
      LINK_DIRECTORIES(${LAPACKE_LIB})
      set(MAC_LAPACKE_LIBRARY -lblas -llapack -llapacke)
    ELSE()
      message(SEND_ERROR "LAPACKE not detected." )
    ENDIF()
  ENDIF()
  # macports paths
  IF(EXISTS "/opt/local/include")
    INCLUDE_DIRECTORIES(/opt/local/include)
  ENDIF()
  IF(EXISTS "/opt/local/lib") 
    LINK_DIRECTORIES(/opt/local/lib) 
  ENDIF()
ENDIF()
#============================================================================== 
set(INSTALL_DIRECTORY "${CMAKE_INSTALL_PREFIX}Nelson-${Nelson_VERSION_MAJOR}.${Nelson_VERSION_MINOR}.${Nelson_VERSION_MAINTENANCE}")
#============================================================================== 
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(LIBRARY_OUTPUT "Nelson-${Nelson_VERSION_MAJOR}.${Nelson_VERSION_MINOR}.${Nelson_VERSION_MAINTENANCE}/bin/macosx64/")
ELSE()
  set(LIBRARY_OUTPUT "Nelson-${Nelson_VERSION_MAJOR}.${Nelson_VERSION_MINOR}.${Nelson_VERSION_MAINTENANCE}/bin/linux${BITNESS}/")
ENDIF()
set(ROOT_OUTPUT "Nelson-${Nelson_VERSION_MAJOR}.${Nelson_VERSION_MINOR}.${Nelson_VERSION_MAINTENANCE}/")
#============================================================================== 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${BIN_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${BIN_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${BIN_DIRECTORY})
#============================================================================== 
set(CPACK_PACKAGE_NAME "Nelson")
set(CPACK_PACKAGE_VENDOR "Allan CORNET")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An numerical software")
set(CPACK_PACKAGE_VERSION_MAJOR ${Nelson_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${Nelson_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${Nelson_VERSION_MAINTENANCE})
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.${Nelson_VERSION_BUILD}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Nelson-${CPACK_PACKAGE_VERSION}")
set(CPACK_GENERATOR "TZ")
include(CPack)
#==============================================================================
add_subdirectory(modules)
add_subdirectory(etc)
add_subdirectory(locale)
add_subdirectory(module_skeleton)
add_subdirectory(resources)
#==============================================================================
install(FILES ${CMAKE_SOURCE_DIR}/COPYING.md DESTINATION ${ROOT_OUTPUT})
install(FILES ${CMAKE_SOURCE_DIR}/CHANGELOG.md DESTINATION ${ROOT_OUTPUT})
install(FILES ${CMAKE_SOURCE_DIR}/CONTRIBUTORS.md DESTINATION ${ROOT_OUTPUT})
install(FILES ${CMAKE_SOURCE_DIR}/README.md DESTINATION ${ROOT_OUTPUT})
install(FILES ${CMAKE_SOURCE_DIR}/THIRDPARTY.md DESTINATION ${ROOT_OUTPUT})
install(FILES ${CMAKE_SOURCE_DIR}/CLA.md DESTINATION ${ROOT_OUTPUT})
#==============================================================================
