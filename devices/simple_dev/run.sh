#!/bin/bash
#
# startup script for distrio simple device
#
# author: Manuel Traut <manut@mecka.net>

LD_LIBRARY_PATH=../../io/lib:../../common:../../manager/lib \
	./distrio_simple_dev \
	-ORBInitRef NameService=corbaloc:iiop:localhost:12345/NameService \
	$@
