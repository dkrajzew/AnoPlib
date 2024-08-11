
SUBDIRS = bin build gfx src

EXTRA_DIST = README ChangeLog AUTHORS COPYING INSTALL NEWS anop.doxyconf

dist-complete: dist
	mv $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-src-$(VERSION).tar.gz
	mv $(PACKAGE)-$(VERSION).zip $(PACKAGE)-src-$(VERSION).zip

AnoPtest$(EXEEXT):
	$(MAKE) -C src $@

