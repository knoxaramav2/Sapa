#Compiles entire SAPA project

SUBDIRS = src/core/
BITVRS=64
GDB=
export BITVRS

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
		./nrn.exe --src Projects/test/test.cns

.PHONY: dbg
dbg:
		./nrn.exe -d --src Projects/test/test.cns

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
