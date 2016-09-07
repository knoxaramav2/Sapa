# Compiles Sapa SDK

CC=g++
CFLAGS= -std=c++14 -pedantic -Wall
LDFLAGS= -g
LIBS= -lm
SRC=DataStruct.cpp LangMap.cpp
OBJ=$(SRC:.cpp=.o)
INCLUDES= -I../headers
OUT=libSapa_Sdk.a
CLEANEXT = o a
BITVRS=64
BITMODE=-DBMODE=$(BITVRS)
EXPORT_PTH=../_bin/

EPATH_FULL=$(EXPORT_PTH)$(BITVRS)/$(OUT)

#configure for Linux and Windows
ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
endif

%.o : %.cpp
	$(CC) $(BITMODE) $(INCLUDES) $(CFLAGS) -c $< $(LIBS)

$(EPATH_FULL): $(OBJ)
	ar rcs $(EPATH_FULL) $(OBJ)


.PHONY: clean
clean:
	rm -f $@ *.o
