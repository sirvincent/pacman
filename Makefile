.PHONY: all
all: test build

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make -j4

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
  cmake -DENABLE_INCLUDE_WHAT_YOU_USE=True -DCMAKE_BUILD_TYPE=Debug .. && \
	make -j4

.PHONY: clean
clean:
	rm -rf build

.PHONY: test
test:

