CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++


DISTRIO_BASE = ../../../

DISTRIO_COMMON := $(DISTRIO_BASE)common
DISTRIO_MANAGER := $(DISTRIO_BASE)manager/lib
DISTRIO_IO := $(DISTRIO_BASE)io/lib
INIPARSER := $(DISTRIO_BASE)/deps/iniparser

LDFLAGS += -L$(DISTRIO_COMMON) -ldistrio_common \
	-L$(DISTRIO_IO) -ldistrio_io \
	-L$(DISTRIO_MANAGER) -ldistrio_manager \
	-lACE -lTAO -lTAO_AnyTypeCode -lTAO_CosNaming -lTAO_PortableServer \
	`pkg-config --libs libgpio` \
	-L. -lini \
	-lrt
CFLAGS += -fPIC -I$(DISTRIO_COMMON) -I$(DISTRIO_IO) -I$(DISTRIO_MANAGER) \
	`pkg-config --cflags libgpio` \
	-I$(INIPARSER)/src

CXXFLAGS += $(CFLAGS)

DESTDIR := /usr

COMPONENT = distrio_generic_gpio
EXEC = $(COMPONENT)
OBJ = generic_gpio.o

all: $(OBJ)
	$(CC) $(CFLAGS) --shared -o libini.so -fPIC ini.c -L$(INIPARSER) -liniparser
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
