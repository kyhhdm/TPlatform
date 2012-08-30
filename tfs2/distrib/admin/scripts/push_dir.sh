#!/bin/bash

#
# Author 	: pb,20080812
# Notes		: script to push job directory across the tfs/mapreduce cluster
#


#sub functions
usage()
{
	echo 	"usage: tfs_push.sh <jobname> <cluster name>"
}

#
#main entry 
#
if [ $# -lt 2 ] ; then
	usage
	exit 1
fi

if [ ! -d "$1" ]; then
    echo "Error: job name $1 is not a valid local directory."
    exit -1
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

echo "user <$USERNAME> start to push local job directory <$JOBNAME> across the <$CLUSTER> cluster"

#
# setup tfs user environment for cexec
#
export C3_CONF=/homeX/tfs/.c3.conf
export C3_PATH=/homeX/tfs/share/c3-4
export C3_RSH=ssh
export C3_USER=tfs
C3HOME=/homeX/tfs/share/c3-4

find $JOBNAME -type f >.tmplist
echo "gawk '{print \$1, \"$INSTALLHOME/user/$USERNAME/\"\$1}' .tmplist >.listfile"
gawk "{print \$1, \"$INSTALLHOME/user/$USERNAME/\"\$1}" .tmplist >.listfile
$C3HOME/cpush $WORKERS: --list=.listfile
