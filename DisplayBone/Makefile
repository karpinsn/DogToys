#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

CC=arm-linux-gnueabi-gcc  

# This should be set to the top most SDK directory
#SDKDIR  = ../../../../..
SDKDIR = /home/karpinsn/Graphics_SDK_4_06_00_03/GFX_Linux_SDK/OGLES2/SDKPackage
OUTNAME = FringeDisplay

#include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

all:
	$(CC) FringeDisplay.o ShaderProgram.o Shader.o PNGLoader.o -o $(OUTNAME)

FringeDisplay.o:
	$(CC) -c FringeDisplay.h FringeDisplay.cpp

ShaderProgram.o:
	$(CC) -c ShaderProgram.h ShaderProgram.cpp

Shader.o:
	$(CC) -c Shader.h Shader.cpp

PNGLoader.o:
	${CC} -c PNGLoader.h PNGLoader.cpp

clean:
	-rm -rf *.o $(OUTNAME)
