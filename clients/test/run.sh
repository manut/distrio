#!/bin/bash
#
# startup script for distrio test
#
# author: Manuel Traut <manut@mecka.net>

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../io/lib:../../common:../../manager/lib \
	./distrio_test \
	-ORBInitRef NameService=corbaloc:iiop:localhost:12345/NameService \
	$@
