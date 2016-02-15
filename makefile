#Compiles entire SAPA project

SUBDIRS = src/core/

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done
