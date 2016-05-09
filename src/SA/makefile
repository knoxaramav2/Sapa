# Compiles Sapa design project

CC=gcc
CFLAGS= -Wall -std=c11
#LIBS= -lm -L/Libs -L. Libs/KNX_Library.a
SRC=Launcher
INCLUDES= -I.
OUT=sapa
CLEANEXT = o a
BITVRS=64
DBGFLAGS= -s --src test.cns
LIBS= -lm -LLibs/$(BITVRS)bit -lKNX_Library

#configure for Linux and Windows
ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT)
endif
#-LLibs -lKNX_Library
$(OUT):$(SRC:=.c)
	$(CC) $(SRC:=.c) $(OSMODE) $(PLATFORM) $(CFLAGS) $(LIBS) -o $(EXPORT_PTH)$(OUT)$(EXT)

dep:
		makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: run
run: $(OUT)
	$(RUNPATH) --src test.cns -s

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
