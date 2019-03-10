
SUBDIRS += BasicData Tester

BASE_DIR = $(shell pwd)

all: build ${SUBDIRS}

BasicData: FORCE
	@${MAKE} -C $@ OUTPUT_PATH=${BASE_DIR}/build

Tester: BasicData FORCE
	@${MAKE} -C $@ OUTPUT_PATH=${BASE_DIR}/build

build:
	mkdir build

FORCE:

clean: clean_subdirs
	-rm build -r

-include ./build_tools/subdirs.mk


