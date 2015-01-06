EXE = clipLine.exe
LIB =
LINK_LIBS = 3dmath logger

OS := $(shell uname -s)
IS_MINGW := $(shell echo $(OS)|grep -i MINGW)

ifdef IS_MINGW
LINK_LIBS += mingw32 wsock32
endif

INCLUDE_DIRS = $(ROOT)/code/graphics/inc \
							 $(ROOT)/code/3dmath/inc \
							 $(ROOT)/code/logger/inc \
							 $(ROOT)/code/video/inc

include $(ROOT)/build/make.rule
