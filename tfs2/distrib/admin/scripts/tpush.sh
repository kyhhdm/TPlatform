#!/bin/bash

#
# Author 	: pb,20080812
# Notes		: script to push job directory across the tfs/mapreduce cluster
#


#sub functions
usage()
{
	echo    "TFS/MapRed Version 0.1"
	echo 	"   Usage: tpush.sh <cluster name> <job local directory>"
    echo    ""
    echo    "   push job local directory onto cluster, preparing data which mapred task needs" 
    echo    ""
    echo    "       cluster name = name of tfs/mapred cluster, see tlist" 
    echo    "       job local dir= local directory which will be distribted to cluster"
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
JOBNAME=$2
CLUSTER=$1
CHUNKSERVERS=$1"_chunkservers"
WORKERS=$1"_workers"

if [ ! -d "$JOBNAME" ]; then
    echo "Error: $JOBNAME is not a valid local directory."
    exit -1
fi

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

echo "user <$USERNAME> start to push local job directory <$JOBNAME> across the <$CLUSTER> cluster"
#step.1 sync local job directory to $USERHOME
if [ ! -d "$USERHOME" ]; then
    echo "Error: user shared home diretory not found at $USERHOME"
    exit -1
fi

if [ ! -d "$USERHOME/$USERNAME" ]; then
    mkdir $USERHOME/$USERNAME
fi

if [ ! -d "$USERHOME/$USERNAME/$JOBNAME/" ]; then
    mkdir $USERHOME/$USERNAME/$JOBNAME
fi

#step.2
rsync -t $JOBNAME/* $USERHOME/$USERNAME/$JOBNAME

#step.3
echo "make job directory and distribute data across cluster..."
$C3HOME/cexec $WORKERS: "if [ ! -d $INSTALLHOME/user/$USERNAME ]; then mkdir $INSTALLHOME/user/$USERNAME; fi; 
    if [ ! -d $INSTALLHOME/user/$USERNAME/$JOBNAME ]; then mkdir $INSTALLHOME/user/$USERNAME/$JOBNAME/; fi;
    rsync -t $USERHOME/$USERNAME/$JOBNAME/* $INSTALLHOME/user/$USERNAME/$JOBNAME"

