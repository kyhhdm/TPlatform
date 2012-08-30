#!/bin/bash
# @file config.h
# @author Chen Rishan
# @date 2007-08-10

## Envirenment. Set the following variables 
# host name or IP address of all the hosts
HOSTS=(build1 build2 build3 build4 build5 build6 build7 build8 build9 build10)
# this user should have write access to the following dir on each of the HOSTS
USERNAME=tfs

# the deployment of TFS system, the number N  stand for the Nth host in the HOSTS array
MASTER_HOST=0
CLIENT_HOSTS=(1)
CHUNKSERVER_HOSTS=(1 2 3 4 5 6 7 8 9)

## the build directory where the executables are
BUILD_DIR=../../build

# name of the executable pragram
MASTER_NAME=tfs_master
CHUNKSERVER_NAME=tfs_chunkserver

# working dir on master or chunkserver machines
MASTER_WORK_DIR=/home/tfs/
CHUNKSERVER_WORK_DIR=/home/tfs/

# the configure files' path
MASTER_CONFIGURE=${MASTER_WORK_DIR}/tfs_master.ini
CHUNKSERVER_CONFIGURE=${CHUNKSERVER_WORK_DIR}/tfs_chunkserver.ini

# log file
MASTER_LOG_FILE=${MASTER_WORK_DIR}/tfs_master.log
CHUNKSERVER_LOG_FILE=${CHUNKSERVER_WORK_DIR}/tfs_chunkserver.log
