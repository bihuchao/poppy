EXE = logserver.exe
LIB =
LINK_LIBS = video graphics 3dmath logger SDL

OS := $(shell uname -s)
IS_MINGW := $(shell echo $(OS)|grep -i MINGW)

ifdef IS_MINGW
LINK_LIBS += mingw32 wsock32
endif

INCLUDE_DIRS =

include $(ROOT)/build/make.rule
