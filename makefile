#Compiles entire SAPA project

SUBDIRS = src/core/

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
		bin_/core/nrn --src test -p

.PHONY: dbg
dbg:
		bin_/core/nrn -d --src test -p

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
