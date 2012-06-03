CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++

DISTRIO_MANAGER := ../../manager/lib
DISTRIO_COMMON := ../../common
DISTRIO_IO := ../../io

LDFLAGS += -L$(DISTRIO_COMMON) -ldistrio_common \
	-L$(DISTRIO_IO) -ldistrio_io \
	-L$(DISTRIO_MANAGER) -ldistrio_manager \
	-lrt -lACE -lTAO -lTAO_AnyTypeCode -lTAO_CosNaming -lTAO_PortableServer
CFLAGS += -fPIC -I$(DISTRIO_COMMON) -I$(DISTRIO_IO) -I$(DISTRIO_MANAGER)
CXXFLAGS += $(CFLAGS)

DESTDIR := /usr

COMPONENT = distrio_simple_dev
EXEC = $(COMPONENT)
OBJ = simple_dev.o

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
