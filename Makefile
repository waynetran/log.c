package = log.c
version = 0.0.1
tarname = $(package)
distdir = $(tarname)-$(version)

all:
	cd src && $(MAKE) $@

test:
	cd src && $(MAKE) $@

clean:
	-rm *~ *.log
	cd src && $(MAKE) $@

distclean: clean FORCE
	-rm -rf test lib
	cd src && $(MAKE) $@

dist: all $(distdir).tar.gz

$(distdir).tar.gz: $(distdir)
	tar chof - $(distdir) | gzip -9 -c > $@
	rm -rf $(distdir)

$(distdir): FORCE clean
	mkdir -p $(distdir)
	cp -r src $(distdir)
	cp  Makefile $(distdir)
	-cp  README.* $(distdir)
	-cp  LICENSE $(distdir)

distcheck: $(distdir).tar.gz
	gzip -cd $(distdir).tar.gz | tar xvf -
	cd $(distdir) && $(MAKE) all
	cd $(distdir) && $(MAKE) clean
	rm -rf $(distdir)
	@echo "*** Package $(distdir).tar.gz is ready for distribution."


install:
	cp lib/liblog.c.a /usr/local/lib
	mkdir -p /usr/local/include/log.c
	cp src/*.h /usr/local/include/log.c

FORCE:
	-rm $(distdir).tar.gz > /dev/null 2>&1
	-rm -rf $(distdir) > /dev/null 2>&1


.PHONY: FORCE all clean dist test install
