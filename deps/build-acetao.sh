#!/bin/bash

cd acetao
cp bin/MakeProjectCreator/modules/* ../MPC/modules/

ACE_ROOT=`pwd`
MPC_ROOT=`pwd`/../MPC
LD_LIBRARY_PATH=$ACE_ROOT/lib:$LD_LIBRARY_PATH

export ACE_ROOT=$ACE_ROOT
export TAO_ROOT=$TAO_ROOT
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH

echo '#include "ace/config-linux.h"' > ace/config.h
echo include $ACE_ROOT/include/makeinclude/platform_linux.GNU > \
	include/makeinclude/platform_macros.GNU
echo "INSTALL_PREFIX = /usr" >> include/makeinclude/platform_macros.GNU
echo "LDFLAGS += -fPIC" >> include/makeinclude/platform_macros.GNU
echo "CFLAGS += -fPIC" >> include/makeinclude/platform_macros.GNU
echo "CXXFLAGS += -fPIC" >> include/makeinclude/platform_macros.GNU
unlink MPC
ln -s ../MPC MPC

unlink TAO
ln -s ../TAO TAO
TAO_ROOT=`pwd`/TAO

echo ACE: $ACE_ROOT
echo TAO: $TAO_ROOT

cd TAO
$ACE_ROOT/bin/mwc.pl -type gnuace TAO_ACE.mwc
cd -
make -j9
sudo ACE_ROOT=$ACE_ROOT TAO_ROOT=$TAO_ROOT make install
cd TAO
$ACE_ROOT/bin/mwc.pl -type gnuace TAO/TAO.mwc
make -j9
sudo ACE_ROOT=$ACE_ROOT TAO_ROOT=$TAO_ROOT make install
