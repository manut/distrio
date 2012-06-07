#!/bin/bash
#
# startup script for distrio generic gpio exporter
#
# author: Manuel Traut <manut@mecka.net>

LD_LIBRARY_PATH=../../lib:../../../common:../../../manager/lib \
	./distrio_generic_gpio \
	-ORBInitRef NameService=corbaloc:iiop:localhost:12345/NameService \
	$@
