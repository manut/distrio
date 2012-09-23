CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++

DISTRIO_BASE = ../../

DISTRIO_MANAGER := $(DISTRIO_BASE)manager/lib
DISTRIO_IO := $(DISTRIO_BASE)io/lib
DISTRIO_COMMON := $(DISTRIO_BASE)common

LDFLAGS += -L$(DISTRIO_COMMON) -ldistrio_common \
	-L$(DISTRIO_IO) -ldistrio_io \
	-L$(DISTRIO_MANAGER) -ldistrio_manager \
	-lrt -lACE -lTAO -lTAO_AnyTypeCode -lTAO_CosNaming -lTAO_PortableServer
CFLAGS += -g -fPIC -I$(DISTRIO_COMMON) -I$(DISTRIO_IO) -I$(DISTRIO_MANAGER)
CXXFLAGS += $(CFLAGS)

DESTDIR := /usr

COMPONENT = distrio_test
EXEC = $(COMPONENT)
OBJ = test.o

all: $(OBJ)
	$(LD) $(LDFLAGS) -o $(EXEC) $(OBJ)

clean:
	rm -f *.o
	rm -f $(EXEC)

install: all
	cp -a $(EXEC) $(DESTDIR)/bin

uninstall:
	rm -f $(DESTDIR)/bin/$(EXEC)

idl:
	/bin/true
