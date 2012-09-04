#--------------------------------------------------------------------------
# Name         : content.mak
# Title        : Makefile to build content files
#
# Copyright    : Copyright (C)  Imagination Technologies Limited.
#              : No part of this software, either material or conceptual 
#              : may be copied or distributed, transmitted, transcribed,
#              : stored in a retrieval system or translated into any 
#              : human or computer language in any form by any means,
#              : electronic, mechanical, manual or other-wise, or 
#              : disclosed to third parties without the express written
#              : permission of VideoLogic Limited, Unit 8, HomePark
#              : Industrial Estate, King's Langley, Hertfordshire,
#              : WD4 8LZ, U.K.
#
# Description  : Makefile to build content files for demos in the PowerVR SDK
#
# Platform     :
#
#--------------------------------------------------------------------------

#############################################################################
## Variables
#############################################################################
PVRTEXTOOL 	= ..\..\..\Utilities\PVRTexTool\PVRTexToolCL\Windows_x86_32\PVRTexTool.exe
FILEWRAP 	= ..\..\..\Utilities\Filewrap\Windows_x86_32\Filewrap.exe
PVRUNISCO 	= ..\..\..\Utilities\PVRUniSCo\OGLES\Windows_x86_32\glslcompiler_sgx535.exe

MEDIAPATH = ../Media
CONTENTDIR = Content

#############################################################################
## Instructions
#############################################################################

TEXTURES = \
	skyline.pvr

BIN_SHADERS = \
	Shaders/TextureDisplay.vsc \
	Shaders/TextureDisplay.fsc

RESOURCES = \
	$(CONTENTDIR)/TextureDisplayFragShader.cpp \
	$(CONTENTDIR)/TextureDisplayVertShader.cpp

all: resources
	
help:
	@echo Valid targets are:
	@echo resources, textures, binary_shaders, clean
	@echo PVRTEXTOOL, FILEWRAP and PVRUNISCO can be used to override the default paths to these utilities.

clean:
	-rm $(RESOURCES)
	-rm $(BIN_SHADERS)
	-rm $(TEXTURES)

resources: 		$(CONTENTDIR) $(RESOURCES)
textures: 		$(TEXTURES)
binary_shaders:	$(BIN_SHADERS)

$(CONTENTDIR):
	-mkdir $@

skyline.pvr: $(MEDIAPATH)/skyline.png
	$(PVRTEXTOOL) -m -fOGLPVRTC4 -i$(MEDIAPATH)/skyline.png -o$@

$(CONTENTDIR)/TextureDisplayVertShader.cpp: TextureDisplay.vsh TextureDisplay.vsc
	$(FILEWRAP)  -s  -o $@ TextureDisplay.vsh
	-$(FILEWRAP)  -oa $@ TextureDisplay.vsc

$(CONTENTDIR)/TextureDisplayFragShader.cpp: TextureDisplay.fsh TextureDisplay.fsc
	$(FILEWRAP)  -s  -o $@ TextureDisplay.fsh
	-$(FILEWRAP)  -oa $@ TextureDisplay.fsc

TextureDisplay.vsc: TextureDisplay.vsh
	$(PVRUNISCO) TextureDisplay.vsh $@  -v 

TextureDisplay.fsc: TextureDisplay.fsh
	$(PVRUNISCO) TextureDisplay.fsh $@  -f 

############################################################################
# End of file (content.mak)
############################################################################
