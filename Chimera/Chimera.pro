# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = Chimera
DESTDIR = ../x64/Debug
CONFIG += debug
DEFINES += NO_WARN_MBCS_MFC_DEPRECATION _CONSOLE _SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS
LIBS += -L"$(NIIVIPATH)/Lib_x64/msc" \
    -L"$(PXIPNPPATH)/winnt/Lib_x64/msc" \
    -L"../../../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/Lib_x64/msc" \
    -L"../../../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/agvisa/Lib_x64/msc" \
    -L"../../../../../../Program Files/boost_1_60_0/lib64-msvc-14.0" \
    -L"$(NOINHERIT)"
PRECOMPILED_HEADER = .\Source\stdafx.h
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(Chimera.pri)
QT += widgets core gui
