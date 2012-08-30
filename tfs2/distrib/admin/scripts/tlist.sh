#!/bin/bash

#
# Author 	: pb,20080812
# Notes		: script to list user job directory across the tfs/mapreduce cluster
#


#sub functions
usage()
{
	echo    "TFS/MapRed Version 0.1"
	echo 	"   Usage: tlist.sh [-g clusterName]"
    echo    ""
    echo    "   list clusters in current system"
    echo    ""
    echo    "       -g clustername  : get client configure file from cluster by name"
    echo    ""
}

#
#main entry 
#
if [ $# -ne 0 -a $# -ne 2 ] ; then
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

if [ $# -eq 2 ] ; then
    if [ "$1" = "-g" ] ; then
        if [ -d $SYSTEMHOME/clusters/$2 ] ; then
            cp $SYSTEMHOME/clusters/$2/tfs_client.ini .
            perl -i -pe "s({USER_NAME})($USER)g;" tfs_client.ini
            echo "ok!, please check the configure file tfs_client.ini"
        else
            echo "$2 not found in current clusters, bye..."
        fi
    else
        usage
        exit 1       
    fi
else
    echo "Current useable clusters are: "
    names=`cd $SYSTEMHOME/clusters ; ls `
    for cluster in $names; do
        echo "  $cluster"
    done
fi
    
