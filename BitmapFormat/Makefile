CC = cl
CCFLAGS = /nologo /Os /MD /GS- /c /w
LIBL = lib
LIBLFLAGS =  /nologo /nodefaultlib
LINK = link
BMP_LINK_FLAGS = /nologo /nodefaultlib /entry:main /release /subsystem:console bitmapheader.lib msvcrt.lib ucrt.lib vcruntime.lib
OUTPUTLIB = @echo Created library file %%~nxl
OUTPUTOBJ = @echo Created source object %%~nxo
OUTPUTEXE = @echo Created executable %%~nxa

all: lib create read grayscale .phony

bitmapheader.obj: 
	@$(CC) $(CCFLAGS) /Fo:bitmapheader bitmapheader.c > nul

lib: bitmapheader.obj
	@$(LIBL) $(LIBLFLAGS) /out:bitmapheader.lib bitmapheader.obj 

read.obj:
	@$(CC) $(CCFLAGS) /Fo:read read.c > nul

create.obj:
	@$(CC) $(CCFLAGS) /Fo:create create.c > nul

grayscale.obj:
	@$(CC) $(CCFLAGS) /Fo:grayscale grayscale.c > nul

create: lib create.obj
	@$(LINK) $(BMP_LINK_FLAGS) create.obj

read: lib read.obj
	@$(LINK) $(BMP_LINK_FLAGS) read.obj

grayscale: lib grayscale.obj
	@$(LINK) $(BMP_LINK_FLAGS) grayscale.obj

.phony:
	@echo.
	@for %%l in (*.lib) do $(OUTPUTLIB)
	@for %%o in (*.obj) do $(OUTPUTOBJ)
	@for %%a in (*.exe) do $(OUTPUTEXE)

clean:
	@echo Deleting all compiled objects
	@del /f /s *.obj *.exe *.dll *.lib
