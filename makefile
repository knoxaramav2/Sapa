#Compiles entire SAPA project

SUBDIRS = src/SDK/ src/core/
BINPATH=$(shell pwd)/bin_
COMMON=-g
BITVRS=64
KLIB=-I ../../../KNX_Libraries/headers -L ../../../KNX_Libraries/_bin/$(BITVRS) -lKNX_Library
export BITVRS
export KLIB
export COMMON
export BINPATH

#component version
VERSION_NRN=-DVERSION=\"0.0.1\"
VERSION_SDK=-DVERSION=\"0.0.1\"

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
		bin_/nrn.exe --src Projects/test/test.cns

.PHONY: dbg
dbg:
		bin_/nrn.exe -d -c --src Projects/test/test.cns

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
