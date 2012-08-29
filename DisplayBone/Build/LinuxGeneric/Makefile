#
# File			Makefile
# Title			Demo makefile
#
# Copyright		Copyright Imagination Technologies Limited.
#

.PHONY: clean

SDKDIR  = ../../../../..
OUTNAME = FringeDisplay

OBJECTS +=	\
           FringeDisplay.o	\
           PNGLoader.o	\
           Shader.o	\
           ShaderProgram.o	\

include $(SDKDIR)/Builds/OGLES2/LinuxGeneric/make_demo.mak

%.o: ../../%.cpp ../../%.h
	$(CC) -c $(COMMON_INCLUDES) $(PLAT_INCLUDES) $(INCLUDES) $(COMMON_CFLAGS) $(PLAT_CFLAGS) $(CFLAGS) $^ -o$@

clean:
	-rm -rf $(PLAT_OBJPATH)/*.o	
