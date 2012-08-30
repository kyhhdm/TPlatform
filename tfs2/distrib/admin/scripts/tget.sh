#!/bin/bash

#
# Author 	: pb,20080812
# Notes		: script to get job log file to local directory from the tfs/mapreduce cluster
#

#sub functions
usage()
{
	echo    "TFS/MapRed Version 0.1"
	echo 	"   Usage: tget.sh <cluster name> <jobid>"
    echo    ""
    echo    "   get job log files from cluster"
    echo    ""
    echo    "       cluster name = name of tfs/mapred cluster, see tlist" 
    echo    "              jobid = jobid of committed mapred job"
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

USERNAME=$USER
JOBNAME=$2
CLUSTER=$1
CHUNKSERVERS=$1"_chunkservers"
WORKERS=$1"_workers"

#
# check up system setup
#
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

echo "<$USERNAME> start to get log files for job <$JOBNAME> from the <$CLUSTER> cluster"
if [ ! -d $JOBNAME ] ; then mkdir $JOBNAME ; fi
$C3HOME/cget $WORKERS:1-100 $INSTALLHOME/jobs/$JOBNAME/$JOBNAME.log $JOBNAME
