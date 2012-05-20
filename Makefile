all:
	mkdir -p ../build
	qmake -o ../build/Makefile digger.pro
	make -C ../build

clean:
	rm -rf ../build/*

.PHONY: all clean