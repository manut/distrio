CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++

DISTRIO_IO = ../io

CFLAGS += -fPIC -I. -I$(DISTRIO_IO)
CXXFLAGS += $(CFLAGS)

TAO_IDL := tao_idl

DESTDIR := /usr

COMPONENT = distrio_common
LIB = lib$(COMPONENT).so
OBJ = $(COMPONENT)C.o $(COMPONENT).o $(COMPONENT)S.o common.o

IDL_CLEANFILES = $(COMPONENT)C.cpp $(COMPONENT)C.inl $(COMPONENT)I.h \
	$(COMPONENT)S.h $(COMPONENT)C.h $(COMPONENT)S.cpp

all: $(OBJ)
	$(LD) -shared -o $(LIB) $(OBJ)

.PHONY: idl
idl:
	$(TAO_IDL) -GI -I../interfaces ../interfaces/$(COMPONENT).idl
	rm -f $(COMPONENT)I.cpp

.PHONY: idl_clean
idl_clean:
	rm -f $(IDL_CLEANFILES)

.PHONY: clean
clean: idl_clean
	rm -f *.o
	rm -f $(LIB)

install: all
	cp -a $(LIB) $(DESTDIR)/lib

uninstall:
	rm -f $(DESTDIR)/lib/$(LIB)
