#Compiles entire SAPA project

SUBDIRS = src/core/

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
		./nrn --src test -p -l -b

.PHONY: dbg
dbg:
		./nrn -d --src test -p -l -b

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
