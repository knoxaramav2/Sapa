#Compiles Sapa Development Kit

CC = g++
BITVRS=64
DEBUG=false
CFLAGS = -std=c++14 -Wall -Iheaders $(COMMON) -g $(VERSION_SDK)
LFLAGS = -lm -Iheaders
DFLAGS = -DDEBUG=$(DEBUG)#build debug arg
OUT = libSDK.so
CLEANEXT = o a
DBGFLAGS= -d#command line debug arg
SRC=sdk.cpp object.cpp cell.cpp
EXPORT_PTH=../../bin_/

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	CFLAGS += -fPIC
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
endif

all:
	$(CC) $(CFLAGS) $(DFLAGS) $(LFLAGS) $(SRC) -shared -o $(EXPORT_PTH)$(OUT) $(OSMODE) $(PLATFORM) $(KLIB)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
