CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++

DISTRIO_BASE = ../

DISTRIO_IO = $(DISTRIO_BASE)io/lib
DISTRIO_MANAGER = $(DISTRIO_BASE)manager/lib

CFLAGS += -g -fPIC -I. -I$(DISTRIO_IO) -I$(DISTRIO_MANAGER)
CXXFLAGS += $(CFLAGS)
LDFLAGS += -lrt

TAO_IDL := tao_idl

DESTDIR := /usr

COMPONENT = distrio_common
LIB = lib$(COMPONENT).so
OBJ = $(COMPONENT)C.o $(COMPONENT).o $(COMPONENT)S.o distrio_helper.o

IDL_CLEANFILES = $(COMPONENT)C.cpp $(COMPONENT)C.inl $(COMPONENT)I.h \
	$(COMPONENT)S.h $(COMPONENT)C.h $(COMPONENT)S.cpp

all: $(OBJ)
	$(LD) $(LDFLAGS) -shared -o $(LIB) $(OBJ)

.PHONY: idl
idl:
	$(TAO_IDL) -GI -I$(DISTRIO_BASE)interfaces \
		$(DISTRIO_BASE)interfaces/$(COMPONENT).idl
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
