#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = /home/karpinsn/Graphics_SDK_4_06_00_02/GFX_Linux_SDK/OGLES2/SDKPackage
OUTNAME = FringeDisplay

OBJECTS += \
           TextureDisplayVertShader.o \
           TextureDisplayFragShader.o \
		   PNGLoader.o

LINK += -lpng

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

../../Content/TextureDisplayVertShader.cpp ../../Content/TextureDisplayFragShader.cpp: build_textures_and_shaders

%.o: ../../Content/%.cpp
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o
	make -C ../.. -f content.mak clean
