CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++

DISTRIO_COMMON := ../../common
DISTRIO_IO := ../../io

LDFLAGS += -L$(DISTRIO_COMMON) -ldistrio_common -L$(DISTRIO_IO) -ldistrio_io \
	-lrt -lACE -lTAO -lTAO_AnyTypeCode -lTAO_CosNaming -lTAO_PortableServer
CFLAGS += -fPIC -I$(DISTRIO_COMMON) -I$(DISTRIO_IO)
CXXFLAGS += $(CFLAGS)

TAO_IDL := tao_idl

DESTDIR := /usr

COMPONENT = distrio_manager
EXEC = $(COMPONENT)
OBJ = $(COMPONENT)C.o $(COMPONENT)S.o $(COMPONENT).o
IDL_CLEANFILES = $(COMPONENT)C.cpp $(COMPONENT)C.h $(COMPONENT)I.h \
	$(COMPONENT)S.cpp $(COMPONENT)S.h $(COMPONENT)C.inl

all: $(OBJ)
	$(LD) $(LDFLAGS) -o $(EXEC) $(OBJ)

idl:
	$(TAO_IDL) -GI -I../../interfaces ../../interfaces/$(COMPONENT).idl
	rm -f $(COMPONENT)I.cpp $(COMPONENT)I.h

idl_clean:
	rm -f $(IDL_CLEANFILES)

clean: idl_clean
	rm -f *.o
	rm -f $(EXEC)

install: all
	cp -a $(EXEC) $(DESTDIR)/bin

uninstall:
	rm -f $(DESTDIR)/bin/$(EXEC)
