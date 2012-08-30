### Makefile --- 

## Author: yzf@net.pku.edu.cn
## Version: $Id: Makefile,v 0.0 2007/11/28 07:25:14 yzf Exp $
## Keywords: 
## X-URL: 

OUTPUT_DIR=../c++/ice-3.1.1
SLICE_CPP=../../../../thirdparty/bin/slice2cpp
SLICE_JAVA=../../../../thirdparty/bin/slice2java
JAVA_OUTPUT_DIR=../java/ice-3.1.1

all: WorkerService.h JobService.h MonitorService.h MonitorService.java


WorkerService.h: WorkerService.ice Address.ice MasterCommand.ice Heartbeat.ice
	${SLICE_CPP} -I. --output-dir ${OUTPUT_DIR} $^
JobService.h: JobService.ice MapReduceJob.ice JobDetail.ice
	${SLICE_CPP} -I. --output-dir ${OUTPUT_DIR} $^
MonitorService.h: MonitorService.ice Address.ice JobDetail.ice TaskDetail.ice MapReduceJob.ice WorkerDetail.ice
	${SLICE_CPP} -I. --output-dir ${OUTPUT_DIR} $^
MonitorService.java: MonitorService.ice Address.ice JobDetail.ice TaskDetail.ice MapReduceJob.ice WorkerDetail.ice
	${SLICE_JAVA} -I. --output-dir ${JAVA_OUTPUT_DIR} $^
### Makefile ends here
