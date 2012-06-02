CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++

TAO_IDL := tao_idl

DESTDIR := /usr

EXEC = distrio-manager
OBJ = managerC.o managerS.o manager.o
IDL_CLEANFILES = managerC.cpp managerC.h managerI.h managerS.cpp managerS.h \
	managerC.inl

all: idl $(OBJ)
	$(LD) -o $(EXEC) $(OBJ)

idl:
	$(TAO_IDL) -GI -I../interfaces ../interfaces/manager.idl
	rm -f managerI.cpp

idl_clean:
	rm -f $(IDL_CLEANFILES)

clean: idl_clean
	rm -f $(EXEC)

install: all
	cp -a $(EXEC) $(DESTDIR)/bin

uninstall:
	rm -f $(DESTDIR)/bin/$(EXEC)
