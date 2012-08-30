#!/bin/bash
# @(#) run.sh
# @author Chen Rishan
# @date 2007-08-10
# @description: run the TFS system

#######################import the config.sh##########################
. ./config.sh
#####################################################################

echo "Starting master on ${HOSTS[${MASTER_HOST}]}";
# copy the executable `master' to master host
echo scp ${BUILD_DIR}/${MASTER_NAME} ${USERNAME}@${HOSTS[${MASTER_HOST}]}:${MASTER_WORK_DIR}
scp ${BUILD_DIR}/${MASTER_NAME} ${USERNAME}@${HOSTS[${MASTER_HOST}]}:${MASTER_WORK_DIR}
# show master config
echo "Content of master's config file ${MASTER_CONFIGURE}@${HOSTS[${MASTER_HOST}]}:"
echo "================================================================"
ssh ${USERNAME}@${HOSTS[${MASTER_HOST}]} "cat ${MASTER_CONFIGURE}"
echo "================================================================"
# run master
echo ssh ${USERNAME}@${HOSTS[${MASTER_HOST}]} "cd ${MASTER_WORK_DIR}; ./${MASTER_NAME} ${MASTER_CONFIGURE}"
ssh ${USERNAME}@${HOSTS[${MASTER_HOST}]} "cd ${MASTER_WORK_DIR}; ./${MASTER_NAME} ${MASTER_CONFIGURE}" &

sleep 2
##########################run the chunkserver#############################
for(( i=0; $i < ${#CHUNKSERVER_HOSTS[*]}; i++ ))
do
  echo "Starting chunkserver on ${HOSTS[${CHUNKSERVER_HOSTS[$i]}]}"
# copy
  echo scp ${BUILD_DIR}/${CHUNKSERVER_NAME} ${USERNAME}@${HOSTS[${CHUNKSERVER_HOSTS[$i]}]}:${CHUNKSERVER_WORK_DIR}
  scp ${BUILD_DIR}/${CHUNKSERVER_NAME} ${USERNAME}@${HOSTS[${CHUNKSERVER_HOSTS[$i]}]}:${CHUNKSERVER_WORK_DIR}
# show config
  echo "Content of chunkserver's config file ${CHUNKSERVER_CONFIGURE}@${HOSTS[${CHUNKSERVER_HOSTS[$i]}]}:"
  echo "================================================================"
  ssh ${USERNAME}@${HOSTS[${CHUNKSERVER_HOSTS[$i]}]} "cat ${CHUNKSERVER_CONFIGURE}"
  echo "================================================================"
# run
  echo ssh ${USERNAME}@${HOSTS[${CHUNKSERVER_HOSTS[$i]}]} "cd ${CHUNKSERVER_WORK_DIR}; ./${CHUNKSERVER_NAME} ${CHUNKSERVER_CONFIGURE}" 
  ssh ${USERNAME}@${HOSTS[${CHUNKSERVER_HOSTS[$i]}]} "cd ${CHUNKSERVER_WORK_DIR}; ./${CHUNKSERVER_NAME} ${CHUNKSERVER_CONFIGURE}" &
done
