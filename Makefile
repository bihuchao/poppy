TARGET=puppyTest.exe
CPP=g++

SRCS=video/FrameBuffer.cc video/FrameBufferOfMem.cc poppy.cc
OBJS=$(patsubst %.cc, %.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CPP) -o $@ $^

%.o: %.cc
	$(CPP) -c -g -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS)
