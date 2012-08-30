#!/bin/bash
# @(#)startup.sh
# AUTHOR: Zhifeng YANG
# CREATED DATE: 2007-12-20
# DESCRIPTION: 
#

# load config
. ./config.sh

echo "Starting master on ${MASTER_HOST}"
# copy the executable `master' to master host
echo scp ${BUILD_DIR}/${MASTER_NAME} ${USERNAME}@${MASTER_HOST}:${MASTER_WORK_DIR}
scp ${BUILD_DIR}/${MASTER_NAME} ${USERNAME}@${MASTER_HOST}:${MASTER_WORK_DIR}
# show master config
echo "=====${MASTER_CONFIG}@${MASTER_HOST}====="
ssh ${USERNAME}@${MASTER_HOST} "cat ${MASTER_CONFIG}"
echo "========================================="
# run master
echo ssh ${USERNAME}@${MASTER_HOST} "ulimit -c unlimited; cd ${MASTER_WORK_DIR}; ./${MASTER_NAME} ${MASTER_CONFIG}"
ssh ${USERNAME}@${MASTER_HOST} "ulimit -c unlimited; cd ${MASTER_WORK_DIR}; ./${MASTER_NAME} ${MASTER_CONFIG}" &
sleep 1


for(( i=0; $i < ${#WORKER_HOSTS[*]}; i++ ))
do
  echo "****************************************************************"
  echo "Starting worker on ${WORKER_HOSTS[$i]}"
# copy
  echo scp ${BUILD_DIR}/${WORKER_NAME} ${USERNAME}@${WORKER_HOSTS[$i]}:${WORKER_WORK_DIR}
  scp ${BUILD_DIR}/${WORKER_NAME} ${USERNAME}@${WORKER_HOSTS[$i]}:${WORKER_WORK_DIR}
# show config
  echo "=============${WORKER_CONFIG}@${WORKER_HOSTS[$i]}================"
  ssh ${USERNAME}@${WORKER_HOSTS[$i]} "cat ${WORKER_CONFIG}"
  echo "================================================================"
# run
  echo ssh ${USERNAME}@${WORKER_HOSTS[$i]} "ulimit -c unlimited; cd ${WORKER_WORK_DIR}; ./${WORKER_NAME} ${WORKER_CONFIG}" 
  ssh ${USERNAME}@${WORKER_HOSTS[$i]} "ulimit -c unlimited; cd ${WORKER_WORK_DIR}; ./${WORKER_NAME} ${WORKER_CONFIG}" &
done
