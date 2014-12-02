TARGET=poppyTest.exe
CPP=g++
CFLAGS= -g -Wall -I./logger -I./video
LFLAGS=-lmingw32 -lSDLmain -lSDL

SRCS=video/FrameBuffer.cc video/Bitmap.cc \
		 logger/Logger.cc math/Vector3.cc \
		 video/FrameBufferSDL.cc \
		 video/VideoSystem.cc \
		 poppy.cc
OBJS=$(patsubst %.cc, %.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CPP) $^ -o $@ $(LFLAGS)

%.o: %.cc
	$(CPP) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS) stderr.txt stdout.txt
