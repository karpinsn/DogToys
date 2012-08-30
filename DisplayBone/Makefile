#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

INCLUDE = -I/home/karpinsn/Workspace/ARM-Libs/usr/include -I/home/karpinsn/Graphics_SDK_4_06_00_03/include/OGLES2/ -I/home/karpinsn/Graphics_SDK_4_06_00_03/GFX_Linux_SDK/OGLES2/SDKPackage/Tools/OGLES2/ -I/home/karpinsn/Graphics_SDK_4_06_00_03/GFX_Linux_SDK/OGLES2/SDKPackage/Shell
LIBDIR = -L/home/karpinsn/Workspace/ARM-Libs/usr/lib -L/home/karpinsn/Graphics_SDK_4_06_00_03/gfx_rel_es3.x 

CC=arm-linux-gnueabi-g++  
CFLAGS=-std=gnu++0x $(INCLUDE)
LIBS = -lpng -lEGL -lGLESv2

# This should be set to the top most SDK directory
#SDKDIR  = ../../../../..
SDKDIR = /home/karpinsn/Graphics_SDK_4_06_00_03/GFX_Linux_SDK/OGLES2/SDKPackage
OUTNAME = FringeDisplay

#include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

all: FringeDisplay.o ShaderProgram.o Shader.o PNGLoader.o
	$(CC) FringeDisplay.o ShaderProgram.o Shader.o PNGLoader.o -o $(OUTNAME) $(LIBDIR) $(LIBS)

FringeDisplay.o:
	$(CC) $(CFLAGS) -c FringeDisplay.h FringeDisplay.cpp

ShaderProgram.o:
	$(CC) $(CFLAGS) -c ShaderProgram.h ShaderProgram.cpp

Shader.o:
	$(CC) $(CFLAGS) -c Shader.h Shader.cpp

PNGLoader.o:
	${CC} $(CFLAGS) -c PNGLoader.h PNGLoader.cpp

clean:
	-rm -rf *.o *.gch $(OUTNAME)
