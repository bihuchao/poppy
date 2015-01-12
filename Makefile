.PHONY: release debug clean

ROOT = $(realpath .)
DIRS = $(ROOT)/code/3dmath/src \
			 $(ROOT)/code/graphics/src \
			 $(ROOT)/code/logger/src \
			 $(ROOT)/code/video/src \
			 $(ROOT)/code/poppy/src \
			 $(ROOT)/code/logserver/src

DIRS += $(ROOT)/test/solid/src
DIRS += $(ROOT)/test/tanks/src \
		$(ROOT)/test/clipLine/src \
		$(ROOT)/test/bresenham/src \
		$(ROOT)/test/roam/src \
		$(ROOT)/test/objectcopy/src

RM = rm
RMFLAGS = -rf
RMS = $(ROOT)/build/exes/release/*.exe $(ROOT)/build/exes/release/*.txt \
		$(ROOT)/build/exes/debug/*.exe $(ROOT)/build/exes/debug/*.txt \
		$(ROOT)/build/libs/


release debug clean:
	@set -e; \
		for dir in $(DIRS); \
		do \
			cd $$dir && $(MAKE) -r ROOT=$(ROOT) $@; \
		done
		@set -e; \
			if [ "$(MAKECMDGOALS)" = "clean" ]; then $(RM) $(RMFLAGS) $(RMS); fi
		@echo ""
		@echo ":-) Completed"
		@echo ""

