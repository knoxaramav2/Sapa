#compiles core component

EXPORT_PTH=../../bin_/
CC = g++
CFLAGS = -std=c++14 -Wall $(COMMON) -g $(VERSION_NRN)
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) -L$(EXPORT_PTH) -l:libSDK.so $(KLIB)
OUT = nrn
CLEANEXT = o a
BITVRS=64
DBGFLAG=
SRC=Launcher.cpp

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)$(EXT)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT)$(EXT)
endif

all:
	$(CC) $(SRC) $(OSMODE) $(CFLAGS) $(PLATFORM) $(LFLAGS) $(KLIB) -o $(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
