# Microsoft Developer Studio Project File - Name="UsbHidDemonstrator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UsbHidDemonstrator - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UsbHidDemonstrator.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UsbHidDemonstrator.mak" CFG="UsbHidDemonstrator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UsbHidDemonstrator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UsbHidDemonstrator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PC/USB HID Demonstrator/SOFTWARE", NBSBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UsbHidDemonstrator - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_VS6_USED" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 LIB/setupapi.lib LIB/hid.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "UsbHidDemonstrator - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_VS6_USED" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 LIB/setupapi.lib LIB/hid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UsbHidDemonstrator - Win32 Release"
# Name "UsbHidDemonstrator - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DesrciptorView.cpp
# End Source File
# Begin Source File

SOURCE=.\FeatureView.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicConfigView.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicView.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\hexeditctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\IconButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Ini.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UsbHidDemonstrator.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbHidDemonstrator.rc
# End Source File
# Begin Source File

SOURCE=.\UsbHidDemonstratorDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DesrciptorView.h
# End Source File
# Begin Source File

SOURCE=.\FeatureView.h
# End Source File
# Begin Source File

SOURCE=.\GraphicConfigView.h
# End Source File
# Begin Source File

SOURCE=.\GraphicView.h
# End Source File
# Begin Source File

SOURCE=.\HexEdit.h
# End Source File
# Begin Source File

SOURCE=.\hexeditctrl.h
# End Source File
# Begin Source File

SOURCE=.\IconButton.h
# End Source File
# Begin Source File

SOURCE=.\Ini.h
# End Source File
# Begin Source File

SOURCE=.\ReportView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UsbHidDemonstrator.h
# End Source File
# Begin Source File

SOURCE=.\UsbHidDemonstratorDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\BULLSEYE.ICO
# End Source File
# Begin Source File

SOURCE=.\capabilities.ico
# End Source File
# Begin Source File

SOURCE=.\DESC.ico
# End Source File
# Begin Source File

SOURCE=".\famous-066.ico"
# End Source File
# Begin Source File

SOURCE=.\GraphicConfig.ico
# End Source File
# Begin Source File

SOURCE=.\GraphicView.ico
# End Source File
# Begin Source File

SOURCE=.\gray.ico
# End Source File
# Begin Source File

SOURCE=".\HID Capabilities.ico"
# End Source File
# Begin Source File

SOURCE=.\LedOff.ico
# End Source File
# Begin Source File

SOURCE=.\LedOn.ico
# End Source File
# Begin Source File

SOURCE=.\MISC14.ICO
# End Source File
# Begin Source File

SOURCE=.\MISC15.ICO
# End Source File
# Begin Source File

SOURCE=.\r1.ico
# End Source File
# Begin Source File

SOURCE=.\Transfere.ico
# End Source File
# Begin Source File

SOURCE=.\USB_Blue.ico
# End Source File
# Begin Source File

SOURCE=.\res\UsbHidDemonstrator.ico
# End Source File
# Begin Source File

SOURCE=.\res\UsbHidDemonstrator.rc2
# End Source File
# End Group
# End Target
# End Project
