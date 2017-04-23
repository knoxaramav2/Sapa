# Compiles neurOn compiler

CC=g++
VERSION=\""1.0.0\""
CFLAGS= -DVERSION=$(VERSION) -DDEV=true -Wall -std=c++14
#LIBS= -lm -L/Libs -L. Libs/KNX_Library.a
SRC=Launcher
INCLUDES= -Iheaders.
OUT=nrn
CLEANEXT = o a
BITVRS=64
DBGFLAGS= -s --src test.cns --path Projects/test/
GDB=
LIBS= -lm -LLibs/$(BITVRS)bit -lKNX_Library -L../SDK/_bin/$(BITVRS) -lSapa_Sdk

#configure for Linux and Windows
ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)$(EXT)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT).exe
endif
#-LLibs -lKNX_Library
$(OUT):$(SRC:=.cpp)
	$(CC) $(SRC:=.cpp) $(OSMODE) $(PLATFORM) $(CFLAGS) $(GDB) $(LIBS) -o $(EXPORT_PTH)$(OUT)$(EXT)

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
