#Compiles entire SAPA project

SUBDIRS = src/core/

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
		bin_/core/nrn --src test

.PHONY: dbg
dbg:
		bin_/core/nrn -d --src test
