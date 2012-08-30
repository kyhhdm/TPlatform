#!/bin/bash

BUILD_DIR=../../build

USERNAME=tfs

MASTER_HOST=build1
WORKER_HOSTS=(build2 build3 build4 build5 build6 build7 build8 build9 build10)

MASTER_NAME=mapred_master
WORKER_NAME=mapred_worker

MASTER_WORK_DIR=/home/tfs
WORKER_WORK_DIR=/home/tfs
WORKER_DATA_DIR=/home/tfs/worker_dir/

MASTER_CONFIG=${MASTER_WORK_DIR}/mapred_master.ini
WORKER_CONFIG=${WORKER_WORK_DIR}/mapred_worker.ini

