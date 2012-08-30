#!/bin/bash

# load config
. ./config.sh

echo "======== ${MASTER_HOST} ========"
ssh ${USERNAME}@${MASTER_HOST} "ps -u ${USERNAME}|grep ${MASTER_NAME}"

for (( i=0 ; $i < ${#WORKER_HOSTS[*]} ; i++ ))
do
  echo "======== ${WORKER_HOSTS[$i]} ========"
  ssh ${USERNAME}@${WORKER_HOSTS[$i]} "ps -u ${USERNAME}|grep ${WORKER_NAME}"
done

