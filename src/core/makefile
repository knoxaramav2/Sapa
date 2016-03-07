# Compiles neurOn compiler

CC=g++
CFLAGS= -Wall -std=c++14
LIBS= -lm -L/Libs -L. Libs/KNX_Library.a
SRC=Launcher Structures Settings Compiler Registry
INCLUDES= -I.
OUT=nrn
CLEANEXT = o a
BITVRS=64

#configure for Linux and Windows
ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin_/core/
	EXT=
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin_/core/
	EXT=.exe
endif

$(OUT):$(SRC:=.cpp)
	$(CC) $(SRC:=.cpp) $(OSMODE) $(CFLAGS) -LLibs -lKNX_Library -o $(EXPORT_PTH)$(OUT)$(EXT)
	#$(CC) -o $(EXPORT_PTH)$(OUT)$(EXT)  $^ $(OSMODE) $(PLATFORM) $(CFLAGS) $(LIBS)
	#$(CC) $(SRC:=.cpp) -LLibs -lKNX_Library -o nrn
	#g++ -o nrn Launcher.cpp -L/Libs -lKNX_Library.a

dep:
		makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC)

.PHONY: clean
clean:
	rm -f $@ *.o
