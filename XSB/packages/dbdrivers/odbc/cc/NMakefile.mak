# Make file for odbc_driver.dll

XSBDIR=..\..\..\..
MYPROGRAM=odbc_driver
DRIVER_MANAGER_LIB="$(XSBDIR)\config\x86-pc-windows\bin\driver_manager.lib"

CPP=cl.exe
OUTDIR=$(XSBDIR)\config\x86-pc-windows\bin
INTDIR=.

ALL : "$(OUTDIR)\$(MYPROGRAM).dll"
	nmake /f NMakefile.mak clean

CLEAN :
	-@erase "$(INTDIR)\$(MYPROGRAM).obj"
	-@erase "$(INTDIR)\$(MYPROGRAM).dll"
	-@erase "$(INTDIR)\$(MYPROGRAM).exp"


CPP_PROJ=/nologo /MT /W3 /EHsc /O2 /I "$(XSBDIR)\config\x86-pc-windows" \
		 /I "$(XSBDIR)\emu" /I "$(XSBDIR)\prolog_includes" \
		 /I "$(XSBDIR)\packages\dbdrivers\cc" \
		 /D "WIN32" /D "WIN_NT" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" \
		 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c 
	

SOURCE=$(MYPROGRAM).c
"$(INTDIR)\$(MYPROGRAM).obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib \
		advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib \
		odbc32.lib odbccp32.lib \
		$(DRIVER_MANAGER_LIB) \
		/nologo /dll \
		/machine:I386 /out:"$(OUTDIR)\$(MYPROGRAM).dll"
LINK32_OBJS=  "$(INTDIR)\$(MYPROGRAM).obj"

"$(OUTDIR)\$(MYPROGRAM).dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<
