#!/bin/bash
# @(#) shutdown.sh
# @author Chen Rishan
# @date 2007-08-10
# @description: shutdown the TFS system

#######################import the config.sh##########################
. ./config.sh
#####################################################################

##########################kill the master#############################

ssh ${USERNAME}@${HOSTS[${MASTER_HOST}]} "killall -9 ${MASTER_NAME}"

##########################kill the chunkserver#############################
for(( i=0; $i < ${#CHUNKSERVER_HOSTS[*]}; i++ ))
do
    ssh ${USERNAME}@${HOSTS[${CHUNKSERVER_HOSTS[$i]}]} "killall -9 ${CHUNKSERVER_NAME}"
done

##########################kill the client#############################

