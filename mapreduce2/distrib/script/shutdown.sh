#!/bin/bash
# @(#)shutdown.sh
# AUTHOR: Zhifeng YANG
# CREATED DATE: 2007-12-20
# DESCRIPTION: kill all mapred processes
#

# load config
. ./config.sh

for (( i=0 ; $i < ${#WORKER_HOSTS[*]} ; i++ ))
do
  echo "======== ${WORKER_HOSTS[$i]} ========"
  ssh ${USERNAME}@${WORKER_HOSTS[$i]} "killall -s SIGKILL ${WORKER_NAME}"
done

echo "======== ${MASTER_HOST} ========"
ssh ${USERNAME}@${MASTER_HOST} "killall -s SIGKILL ${MASTER_NAME}"
