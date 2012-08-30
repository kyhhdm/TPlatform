#!/bin/bash
# @(#) logcheck.sh
# @author Chen Rishan
# @date 2007-08-12
# @description: check the log files

#######################import the config.sh##########################
. ./config.sh
#####################################################################
if test $# -ne 1
then 
    echo "Usage: logcheck.sh master|chunkserver [chunkserver_no]"
    exit 0
fi
######!! make sure you are on build1 when you run the script !!######

i=0;
##########################check the master log###########################
if test "$1" = master
then 
    ssh ${USERNAME}@${HOSTS[${MASTER_HOST}]} "tail ${MASTER_LOG_FILE}"
fi
#######################check the chunkserver log#########################
if test "$1" = chunkserver
    then 
    ssh ${USERNAME}@${HOSTS[${CHUNKSERVER_HOSTS[$2]}]} "tail ${CHUNKSERVER_LOG_FILE}"
fi
##########################check the client log###########################
#if test "$1" = client
#then
#    ssh ${USERNAME}@${HOSTS[$i]} cat ${CLIENT_LOG_DIR}${CLIENT_NAME}.log
#fi
