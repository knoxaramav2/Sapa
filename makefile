#Compiles entire SAPA project

SUBDIRS = src/core/ src/SA/

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

.PHONY: sapa
sapa:
		./sapa dev.ctm

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
