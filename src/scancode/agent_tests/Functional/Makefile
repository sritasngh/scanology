# Copyright Siemens AG 2014
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.

TOP = ../../../..
VARS = $(TOP)/Makefile.conf
DEPS = $(TOP)/Makefile.deps
include $(VARS)

LOCALAGENTDIR = ../../agent

test: test-sched

all: version
	$(MAKE) -C $(LOCALAGENTDIR) scancode
	ln -fs $(LOCALAGENTDIR)/scancode ./scancode

all-cov: version
	$(MAKE) -C $(LOCALAGENTDIR) scancode_cov
	ln -fs $(LOCALAGENTDIR)/scancode_cov ./scancode

version:
	$(MAKE) -C $(LOCALAGENTDIR)/.. VERSIONFILE

test-sched: all
	@echo "make functional tests for scheduler mode"
	$(PHPUNIT) --bootstrap $(PHPUNIT_BOOT) schedulerTest.php

coverage: coverage-sched

coverage-sched: all-cov
	@echo "make functional tests for scheduler mode with coverage"
	$(PHPUNIT) --bootstrap $(PHPUNIT_BOOT) schedulerTest.php

clean:
	@echo "nothing to do"
	rm -rf scancode

.PHONY: all test coverage clean

include $(DEPS)
