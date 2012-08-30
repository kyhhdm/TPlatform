#!/bin/sh

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
fi

#usage
usage(){
    echo "usage: check_cluster.sh <CHUNKSERVERS> <MAPRED_WORKERS> <INSTALL_ROOT>"
    echo "  CHUNKSERVERS    cluster name in c3.conf which runs tfs chunkserver, the first machine runs tfs master"
    echo "  MAPRED_WORKERS  cluster name in c3.conf which runs mapreduce workers, the first machine runs mapreduce master"
    echo "  INSTALL_ROOT    tianwang platform system runtime root directory"
    exit 0
}

if [ $# -lt 2 ]; then
    usage
fi


#
# please configure your system bellow
# refer your c3.conf for cluster configuration
#
CHUNKSERVER_CLUSTER=$1
WORKER_CLUSTER=$2
INSTALL_ROOT=$3

#
# check up
#


#
# start the servers
#

#
# check the result
#
echo "checking tfs cluster..."
cexec $CHUNKSERVER_CLUSTER: "ps -A |grep -i tfs"
echo "checking mapreduce cluster..."
cexec $WORKER_CLUSTER: "ps -A |grep -i mapred"


