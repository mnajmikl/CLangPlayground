CC = cl
LIBL = lib
LINK = link

all: lib create read grayscale

lib: bitmapheader.obj
	$(LIBL) /out:bitmapheader.lib bitmapheader.obj

create: lib create.obj
	$(LINK) /release /subsystem:console create.obj bitmapheader.lib

read: lib read.obj
	$(LINK) /release /subsystem:console read.obj bitmapheader.lib

grayscale: lib grayscale.obj
	$(LINK) /release /subsystem:console grayscale.obj bitmapheader.lib

bitmapheader.obj: bitmapheader.c bitmapheader.h
	$(CC) /Wall /O2 /MD /GS- /c /Fo:bitmapheader bitmapheader.c

read.obj : read.c
	$(CC) /Wall /O2 /MD /GS- /c /Fo:read read.c

create.obj : create.c
	$(CC) /Wall /O2 /MD /GS- /c /Fo:create create.c

grayscale.obj : grayscale.c
	$(CC) /Wall /O2 /MD /GS- /c /Fo:grayscale grayscale.c

clean:
	del /f /q *.obj *.exe *.dll *.lib