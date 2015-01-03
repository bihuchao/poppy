EXE = solid.exe
LIB =
LINK_LIBS = video graphics 3dmath logger SDL

OS := $(shell uname -s)
IS_MINGW := $(shell echo $(OS)|grep -i MINGW)

ifdef IS_MINGW
LINK_LIBS += mingw32 SDLmain SDL wsock32
endif

INCLUDE_DIRS = $(ROOT)/code/graphics/inc \
							 $(ROOT)/code/3dmath/inc \
							 $(ROOT)/code/logger/inc \
							 $(ROOT)/code/video/inc

include $(ROOT)/build/make.rule
