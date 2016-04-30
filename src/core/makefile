# Compiles neurOn compiler

CC=g++
CFLAGS= -Wall -std=c++14
#LIBS= -lm -L/Libs -L. Libs/KNX_Library.a
SRC=Launcher Error Project Registry Scanner LexUtil PreCompiler
INCLUDES= -I.
OUT=nrn
CLEANEXT = o a
BITVRS=64
DBGFLAGS= -s --src test.cns
LIBS= -lm -LLibs/$(BITVRS)bit -lKNX_Library

#configure for Linux and Windows
ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin_/core/
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin_/core/
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT)
endif
#-LLibs -lKNX_Library
$(OUT):$(SRC:=.cpp)
	$(CC) $(SRC:=.cpp) $(OSMODE) $(PLATFORM) $(CFLAGS) $(LIBS) -o $(EXPORT_PTH)$(OUT)$(EXT)
	#$(CC) -o $(EXPORT_PTH)$(OUT)$(EXT)  $^ $(OSMODE) $(PLATFORM) $(CFLAGS) $(LIBS)
	#$(CC) $(SRC:=.cpp) -LLibs -lKNX_Library -o nrn
	#g++ -o nrn Launcher.cpp -L/Libs -lKNX_Library.a

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
