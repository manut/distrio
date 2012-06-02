CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++

TAO_IDL := tao_idl

DESTDIR := /usr

LIB = libdistrio_common.so
OBJ = commonC.o common.o commonS.o

IDL_CLEANFILES = commonC.cpp commonC.inl commonI.h commonS.h commonC.h \
	commonS.cpp

all: idl $(OBJ)
	$(LD) -shared -o $(LIB) $(OBJ)

idl:
	$(TAO_IDL) -GI -I../interfaces ../interfaces/common.idl
	rm -f commonI.cpp

idl_clean:
	rm -f $(IDL_CLEANFILES)

clean: idl_clean
	rm -f $(LIB)

install: all
	cp -a $(LIB) $(DESTDIR)/lib

uninstall:
	rm -f $(DESTDIR)/lib/$(LIB)
