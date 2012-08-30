### Makefile --- 

## Author: yzf@net.pku.edu.cn
## Version: $Id: Makefile,v 0.0 2007/03/14 03:00:45 yzf Exp $
## Keywords: 
## X-URL: 


### Makefile ends here
OUTPUT_DIR=../c++/ice-3.1.1
SLICE_CPP=../../../thirdparty/bin/slice2cpp
SLICE_JAVA=../../../thirdparty/bin/slice2java
JAVA_OUTPUT_DIR=../java/ice-3.1.1

all: ClientService.h ChunkServerService.h AdminService.h AdminService.java ClientService.java


ClientService.h: ClientService.ice Exceptions.ice Chunk.ice Address.ice FileInfo.ice
	${SLICE_CPP} -I. --output-dir ${OUTPUT_DIR} $^

ChunkServerService.h: ChunkServerService.ice Address.ice Heartbeat.ice MasterCommand.ice
	${SLICE_CPP} -I. --output-dir ${OUTPUT_DIR} $^

AdminService.h: AdminService.ice Address.ice
	${SLICE_CPP} -I. --output-dir ${OUTPUT_DIR} $^

AdminService.java: AdminService.ice Address.ice
	${SLICE_JAVA} -I. --output-dir ${JAVA_OUTPUT_DIR} $^

ClientService.java: ClientService.ice Exceptions.ice Chunk.ice Address.ice FileInfo.ice
	${SLICE_JAVA} -I. --output-dir ${JAVA_OUTPUT_DIR} $^
