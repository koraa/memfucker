GCC  = gcc
LIBS = -lstdc++

RELEASE_FLAGS = -Ofast -Wall
DEBUG_FLAGS  = -O0 -Wall -g3 -v -fdump-final-insns=rtl -fmem-report -fstack-usage -save-temps

RELEASE_NAME = memfucker
DEBUG_NAME = memfucker_debug

IFILE = memfucker.c

# Amount of memory to alloc on autorun, Megs
STD_FILE_ALLOC = 1024

release :
	$(GCC) $(IFILE) $(LIBS) $(RELEASE_FLAGS) -o $(RELEASE_NAME)

debug :
	$(GCC) $(IFILE) $(LIBS) $(DEBUG_FLAGS) -o $(DEBUG_NAME)

####################

run : release
	./$(RELEASE_NAME) $(STD_FILE_ALLOC)

dbrun : debug
	./$(DEBUG_NAME) $(STD_FILE_ALLOC)

gdb : debug
	@echo "--------------------------------------------------"
	gdb --args ./$(DEBUG_NAME) $(STD_FILE_ALLOC)

#####################

clean :
	rm -f *.ii *.i *.o *.s *.su rtl $(RELEASE_NAME) $(DEBUG_NAME)