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
    echo "usage: shutdown_cluster.sh <CHUNKSERVERS> <MAPRED_WORKERS> <INSTALL_ROOT>"
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
# shutdown the servers
#
echo "shutdown tfs_master..."
cexec $CHUNKSERVER_CLUSTER:0 "killall tfs_master"
echo "shutdown mapred_master..."
cexec $WORKER_CLUSTER:0 "killall mapred_master"
echo "shutdown tfs_chunkservers..."
cexec $CHUNKSERVER_CLUSTER:1-100 "killall tfs_chunkserver"
echo "shutdown mapred_workers..."
cexec $WORKER_CLUSTER:1-100 "killall mapred_worker"

#
# check the result
#
cexec $CHUNKSERVER_CLUSTER: "ps -A |grep -i tfs"
cexec $WORKER_CLUSTER: "ps -A |grep -i mapred"


