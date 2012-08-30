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
    echo "usage: make_cluster.sh <CHUNKSERVERS> <MAPRED_WORKERS> <SERVER_PORT> <INSTALL_ROOT>"
    echo "  CHUNKSERVERS    cluster name in c3.conf which runs tfs chunkserver, the first machine runs tfs master"
    echo "  MAPRED_WORKERS  cluster name in c3.conf which runs mapreduce workers, the first machine runs mapreduce master"
    echo "  SERVER_PORT     listen port for tfs service, and mapreduce listens on port+1000"
    echo "  INSTALL_ROOT    tianwang platform system runtime root directory"
    exit 0
}

if [ ! $# -eq 4 ]; then
    usage
fi


#
# please configure your system bellow
# refer your c3.conf for cluster configuration
#
CHUNKSERVER_CLUSTER=$1
WORKER_CLUSTER=$2
LISTEN_PORT=$3
INSTALL_ROOT=$4

TFS_MASTER_IP=`cname $CHUNKSERVER_CLUSTER: 0 |grep name: |cut --delimiter=: -f 3`
MAPRED_MASTER_IP=`cname $WORKER_CLUSTER: 0 |grep name: |cut --delimiter=: -f 3`
TFS_MASTER_PORT=$LISTEN_PORT
MAPRED_MASTER_PORT=`expr $LISTEN_PORT + 1000`

#
# save configure 
#
echo "INSTALLHOME=$INSTALL_ROOT" >> $SYSTEMHOME/configure

#
# mkdirs
#
cexec $CHUNKSERVER_CLUSTER: $WORKER_CLUSTER: "mkdir $INSTALL_ROOT; mkdir $INSTALL_ROOT/bin; mkdir $INSTALL_ROOT/conf; 
mkdir $INSTALL_ROOT/log; mkdir $INSTALL_ROOT/user; mkdir $INSTALL_ROOT/jobs; mkdir $INSTALL_ROOT/chunks; mkdir $INSTALL_ROOT/chunks/chunks_store; mkdir $INSTALL_ROOT/chunks/chunks_tmp"

#
# install system programs
#
cexec $CHUNKSERVER_CLUSTER: "rsync -t $BINHOME/tfs_* $INSTALL_ROOT/bin"
cexec $WORKER_CLUSTER: "rsync -t $BINHOME/mapred_* $INSTALL_ROOT/bin"

#
# make configuration files
#
#cexec $CHUNKSERVER_CLUSTER: $WORKER_CLUSTER: "sh $LIBHOME/make_configure.sh $TFS_MASTER_IP $TFS_MASTER_PORT $MAPRED_MASTER_IP $MAPRED_MASTER_PORT $INSTALL_ROOT"
cexec $WORKER_CLUSTER: "sh $LIBHOME/make_configure.sh $TFS_MASTER_IP $TFS_MASTER_PORT $MAPRED_MASTER_IP $MAPRED_MASTER_PORT $INSTALL_ROOT"


