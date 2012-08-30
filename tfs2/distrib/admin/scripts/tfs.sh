#!/bin/bash

#
# Author 	: pb,20080807
# Notes		: script to control the tfs/mapreduce cluster
# Argument	:
#	start	: start the cluster
#	show	: show cluster status
#	stop	: shutdown the cluster
#


#sub functions
usage()
{
	echo 	"usage: tfs.sh <start|show|check|stop|shutdown> <cluster name>"
    echo    "	start	: start the cluster"
    echo    "	show	: show cluster status"
    echo    "	stop	: shutdown the cluster"
    echo    "   cluster name : user configured cluster name by make_cluster.sh"
}

#
#main entry 
#
if [ $# -lt 2 ] ; then
	usage
	exit 1
fi

#
# ENVIRONMENT SETUP
#
CONFIG_FILE=`dirname $0`/configure
if [ -f $CONFIG_FILE ]; then
    source $CONFIG_FILE
else    
    SYSTEMHOME="/homeX/tfs/share/system/"
    LIBHOME="/homeX/tfs/share/system/scripts/"
    CONFHOME="/homeX/tfs/share/system/conf/"
    BINHOME="/homeX/tfs/share/system/bin/"
    INSTALLHOME="/home/tfs/tianwang/"
fi

CLUSTER=$2
CHUNKSERVERS=$2"_chunkservers"
WORKERS=$2"_workers"

case "$1" in
"start")
    sh $LIBHOME/start_cluster.sh $CHUNKSERVERS $WORKERS $INSTALLHOME
    ;;
"show")
    sh $LIBHOME/check_cluster.sh $CHUNKSERVERS $WORKERS $INSTALLHOME
	;;
"stop")
    sh $LIBHOME/shutdown_cluster.sh $CHUNKSERVERS $WORKERS $INSTALLHOME
	;;
"*")
	usage
	;;
esac

