#!/bin/bash
#
# startup script for distrio manager
#
# checks if a naming service is running
#  if not; a newone is started before distrio_manager
#
# author: Manuel Traut <manut@mecka.net>

NS_PORT=12345

NS=`ps aux | grep tao_cosnaming | grep $NS_PORT`

if [ -z "$NS" ]; then
	echo start naming service
	tao_cosnaming -ORBEndPoint iiop://localhost:$NS_PORT &
	sleep 1
fi

LD_LIBRARY_PATH=../../io:../../common ./distrio_manager \
	-ORBInitRef NameService=corbaloc:iiop:localhost:12345/NameService \
	$@
