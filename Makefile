TARGET=poppy.exe
CPP=g++
CFLAGS= -g -Wall -I./logger -I./video -I./math
LFLAGS=-lmingw32 -lSDLmain -lSDL

SRCS=video/FrameBuffer.cc video/Bitmap.cc \
		 logger/Logger.cc math/Vector3.cc \
		 video/FrameBufferSDL.cc \
		 video/VideoSystem.cc video/VideoSystemSDL.cc \
		 math/Line2.cc\
		 poppy.cc
OBJS=$(patsubst %.cc, %.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $^ -o $@ $(LFLAGS)

%.o: %.cc
	$(CPP) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS) stderr.txt stdout.txt
