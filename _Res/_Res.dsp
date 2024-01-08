# Microsoft Developer Studio Project File - Name="_Res" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=_Res - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "_Res.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "_Res.mak" CFG="_Res - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "_Res - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "_Res - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "_Res - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_RES_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_RES_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "_Res - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_RES_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_RES_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "_Res - Win32 Release"
# Name "_Res - Win32 Debug"
# Begin Group "md"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\MayKre.MD
# End Source File
# Begin Source File

SOURCE=..\..\..\Acr\MayLut.MD
# End Source File
# Begin Source File

SOURCE=..\..\..\Acr\SpnAlb.md
# End Source File
# Begin Source File

SOURCE=..\..\..\Acr\SpnMus.MD
# End Source File
# Begin Source File

SOURCE=..\..\..\Acr\SpnS15.MD
# End Source File
# End Group
# Begin Group "Nations"

# PROP Default_Filter ""
# Begin Group "Deloware"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\Delavar.nds
# End Source File
# Begin Source File

SOURCE=..\DelNation.cpp
# End Source File
# Begin Source File

SOURCE=..\DelNation.h
# End Source File
# End Group
# Begin Group "May"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\May.NDS
# End Source File
# Begin Source File

SOURCE=..\MayNation.cpp
# End Source File
# Begin Source File

SOURCE=..\MayNation.h
# End Source File
# End Group
# Begin Group "Spain"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\spain.nds
# End Source File
# Begin Source File

SOURCE=..\SpnNation.cpp
# End Source File
# Begin Source File

SOURCE=..\SpnNation.h
# End Source File
# End Group
# Begin Group "Aztecs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\Actec.nds
# End Source File
# Begin Source File

SOURCE=..\AztNation.cpp
# End Source File
# Begin Source File

SOURCE=..\AztNation.h
# End Source File
# End Group
# Begin Group "Hurons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\HurNation.cpp
# End Source File
# Begin Source File

SOURCE=..\HurNation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Acr\Huroni.nds
# End Source File
# End Group
# Begin Group "Iroqezi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\Irokez.nds
# End Source File
# Begin Source File

SOURCE=..\IroNation.cpp
# End Source File
# Begin Source File

SOURCE=..\IroNation.h
# End Source File
# End Group
# Begin Group "Pueblo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\Pueblo.NDS
# End Source File
# Begin Source File

SOURCE=..\PueNation.cpp
# End Source File
# Begin Source File

SOURCE=..\PueNation.h
# End Source File
# End Group
# Begin Group "Incs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\Incas.nds
# End Source File
# Begin Source File

SOURCE=..\IncNation.cpp
# End Source File
# Begin Source File

SOURCE=..\IncNation.h
# End Source File
# End Group
# Begin Group "Siu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\Siu.nds
# End Source File
# Begin Source File

SOURCE=..\SiuNation.cpp
# End Source File
# Begin Source File

SOURCE=..\SiuNation.h
# End Source File
# End Group
# Begin Group "France"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\FraNation.cpp
# End Source File
# Begin Source File

SOURCE=..\FraNation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Acr\France.nds
# End Source File
# End Group
# Begin Group "England"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\england.nds
# End Source File
# Begin Source File

SOURCE=..\EngNation.cpp
# End Source File
# Begin Source File

SOURCE=..\EngNation.h
# End Source File
# End Group
# Begin Group "USA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Acr\USA.nds
# End Source File
# Begin Source File

SOURCE=..\USANation.cpp
# End Source File
# Begin Source File

SOURCE=..\USANation.h
# End Source File
# End Group
# End Group
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Group "AICity"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AICity.cpp
# End Source File
# Begin Source File

SOURCE=..\AICity.h
# End Source File
# End Group
# Begin Group "Import"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AddScenario.h
# End Source File
# Begin Source File

SOURCE=..\AiPurpose.h
# End Source File
# Begin Source File

SOURCE=..\Import.h
# End Source File
# Begin Source File

SOURCE=..\OneObj.h
# End Source File
# End Group
# End Group
# Begin Group "old"

# PROP Default_Filter ""
# Begin Group "AI 0"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Ai0\AIArmy0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIArmy0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBase0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBase0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBranch0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBranch0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBrigade0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBrigade0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBuilding0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIBuilding0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIEnemyArmy0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIEnemyArmy0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIHeader0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIOrder0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIOrder0.h
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIPlayer0.cpp
# End Source File
# Begin Source File

SOURCE=..\Ai0\AIPlayer0.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=..\..\..\Acr\Text\AI.txt
# End Source File
# End Target
# End Project
