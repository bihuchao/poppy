.PHONY: all clean

ROOT = $(realpath .)
DIRS = $(ROOT)/code/3dmath/src \
			 $(ROOT)/code/graphics/src \
			 $(ROOT)/code/logger/src \
			 $(ROOT)/code/video/src \
			 $(ROOT)/code/poppy/src \
			 $(ROOT)/code/logserver/src

DIRS += $(ROOT)/test/solid/src
DIRS += $(ROOT)/test/tanks/src

RM = rm
RMFLAGS = -rf
RMS = $(ROOT)/build/exes/*.exe $(ROOT)/build/libs/*.a \
			$(ROOT)/build/exes/*.txt

all clean:
	@set -e; \
		for dir in $(DIRS); \
		do \
			cd $$dir && $(MAKE) ROOT=$(ROOT) $@; \
		done
		@set -e; \
			if [ "$(MAKECMDGOALS)" = "clean" ]; then $(RM) $(RMFLAGS) $(RMS); fi
		@echo ""
		@echo ":-) Completed"
		@echo ""

