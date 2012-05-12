GCC  = gcc
LIBS = -lstdc++

RELEASE_FLAGS = -Ofast -Wall
DEBUG_FLAGS  = -O0 -Wall -g3 -v -fdump-final-insns=rtl -fmem-report -fstack-usage -save-temps

RELEASE_NAME = memfucker
DEBUG_NAME = memfucker_debug

IFILE = memfucker.c

release :
	$(GCC) $(IFILE) $(LIBS) $(RELEASE_FLAGS) -o $(RELEASE_NAME)

debug :
	$(GCC) $(IFILE) $(LIBS) $(DEBUG_FLAGS) -o $(DEBUG_NAME)

clean :
	rm *.ii *.o *.s *.su rtl $(RELEASE_NAME) $(DEBUG_NAME)