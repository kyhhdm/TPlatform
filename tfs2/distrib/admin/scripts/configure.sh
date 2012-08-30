#!/bin/sh

#
# This is the configuration sciprt to setup working environment
#
STARTUP_HOME=`dirname $0`
SYSTEM_HOME=`dirname $STARTUP_HOME`

echo "SYSTEMHOME=$SYSTEM_HOME" > $SYSTEM_HOME/.configure   
echo "SYSTEMHOME=$SYSTEM_HOME"

echo "LIBHOME=$SYSTEM_HOME/scripts" >> $SYSTEM_HOME/.configure
echo "LIBHOME=$SYSTEM_HOME/scripts" 

echo "CONFHOME=$SYSTEM_HOME/conf"   >> $SYSTEM_HOME/.configure
echo "CONFHOME=$SYSTEM_HOME/conf"   

echo "BINHOME=$SYSTEM_HOME/bin"   >> $SYSTEM_HOME/.configure
echo "BINHOME=$SYSTEM_HOME/bin"   

echo "USERHOME=$SYSTEM_HOME/../user"   >> $SYSTEM_HOME/.configure
echo "USERHOME=$SYSTEM_HOME/../user"   
echo "ok!"
