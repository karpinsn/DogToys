#
# File			Makefile
# Title			FringeDisplay Makefile for beaglebone DisplayBone
# Author		Nik Karpinsky
#
# Copyright		Nik Karpinsky
#

###################################################
# These need to be changed for your specific system
###################################################
# This should be the location of your cross compiling toolchain usr directory
TOOLCHAINDIR=/usr/local/angstrom/arm/arm-angstrom-linux-gnueabi
# This should be set to the SDK directory containing the correct includes (.h)
SGXINCDIR = /home/karpinsn/Workspace/Graphics_SDK_4_06_00_02/include/OGLES2
# This should be set to the SDK directory containing the correct libs (.so)
#SGXLIBDIR = /home/karpinsn/Workspace/Graphics_SDK_4_06_00_02/gfx_rel_es3.x
SGXLIBDIR = /home/karpinsn/Workspace/Graphics_SDK_4_06_00_02/GFX_Linux_SDK/OGLES2/SDKPackage/Builds/OGLES2/LinuxARMV7/Lib
# This should be set to the SDK directory containing the tools and PVR stuff
SGXSDKDIR = /home/karpinsn/Workspace/Graphics_SDK_4_06_00_02/GFX_Linux_SDK/OGLES2/SDKPackage

####################
# Includes and Libs to use
####################
INCLUDE = -I$(TOOLCHAINUSRDIR)/usr/include -I$(SGXINCDIR) -I$(SGXSDKDIR)/Tools -I$(SGXSDKDIR)/Tools/OGLES2 -I$(SGXSDKDIR)/Shell
LIBDIR = -L$(TOOLCHAINUSRDIR)/usr/lib -L$(SGXLIBDIR) 

# The compiler that we should use (should be the cross compiler)
#CC=$(TOOLCHAINDIR)/bin/gcc
CC=/usr/local/angstrom/arm/bin/arm-angstrom-linux-gnueabi-g++
CFLAGS=$(INCLUDE) -I/usr/include/i386-linux-gnu/
LIBS = -lpng -lEGL -lGLESv2 

# What you want the final executable to be called
OUTNAME = FringeDisplay

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
