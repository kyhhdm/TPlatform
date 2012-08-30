#!/bin/bash

#
# Author 	: pb,20080812
# Notes		: script to get job log file to local directory from the tfs/mapreduce cluster
#


#sub functions
usage()
{
	echo 	"usage: get_log.sh <jobid> <cluster name>"
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
    USERHOME="/homeX/tfs/share/user/"
    INSTALLHOME="/home/tfs/tianwang/"
fi

USERNAME=$USER
JOBNAME=$1
CLUSTER=$2
CHUNKSERVERS=$2"_chunkservers"
WORKERS=$2"_workers"

echo "<$USERNAME> start to get log files for job <$JOBNAME> from the <$CLUSTER> cluster"

#
# setup tfs user environment for cexec
#
export C3_CONF=/homeX/tfs/.c3.conf
export C3_PATH=/homeX/tfs/share/c3-4
export C3_RSH=ssh
export C3_USER=tfs
C3HOME=/homeX/tfs/share/c3-4

$C3HOME/cget $WORKERS:1-100 $INSTALLHOME/jobs/$JOBNAME/$JOBNAME.log
