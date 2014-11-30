TARGET=poppyTest.exe
CPP=g++
CFLAGS= -g -Wall
LFLAGS=-lmingw32 -lSDLmain -lSDL

SRCS=video/FrameBuffer.cc video/Bitmap.cc \
		 logger/Logger.cc math/Vector3.cc \
		 poppy.cc
OBJS=$(patsubst %.cc, %.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CPP) $^ -o $@ $(LFLAGS)

%.o: %.cc
	$(CPP) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS)
