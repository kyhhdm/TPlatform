#!/bin/bash

#
# Author 	: pb,20080812
# Notes		: script to list user job directory across the tfs/mapreduce cluster
#


#sub functions
usage()
{
	echo    "TFS/MapRed Version 0.1"
	echo 	"   Usage: tdir.sh <cluster name> <dir name>"
    echo    ""
    echo    "   list user job directory on the cluster"
    echo    ""
    echo    "       cluster name = name of tfs/mapred cluster, see tlist" 
    echo    "           dir name = user job directory name on cluster node"
    echo    ""
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
SHAREHOME="/homeX/tfs/share"

CONFIG_FILE=$SHAREHOME/system/.configure
if [ -f $CONFIG_FILE ]; then
    source $CONFIG_FILE
else    
    echo "System configure file not found, go on by default settings..."    
    SYSTEMHOME="/homeX/tfs/share/system/"
    LIBHOME="/homeX/tfs/share/system/scripts/"
    CONFHOME="/homeX/tfs/share/system/conf/"
    BINHOME="/homeX/tfs/share/system/bin/"
    USERHOME="/homeX/tfs/share/user/"
    INSTALLHOME="/home/tfs/tianwang/"
fi

#
#
#
USERNAME=$USER
DIRNAME=$2
CLUSTER=$1
CHUNKSERVERS=$1"_chunkservers"
WORKERS=$1"_workers"

if [ ! -d $SYSTEMHOME/clusters/$CLUSTER ] ; then
    echo "Cluster <$CLUSTER> not exist, please contact with your cluster manager"
    exit -2
fi

#
# setup tfs user environment for cexec
#
export C3_CONF=/homeX/tfs/.c3.conf
export C3_PATH=/homeX/tfs/share/c3-4
export C3_RSH=ssh
export C3_USER=tfs
C3HOME=/homeX/tfs/share/c3-4

echo "$USERNAME's job directory $JOBNAME on $CLUSTER:"
$C3HOME/cexec $WORKERS: "ls -l $INSTALLHOME/user/$USERNAME/$DIRNAME"
