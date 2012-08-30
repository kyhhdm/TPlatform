### Makefile --- 

## Author: yzf@net.pku.edu.cn
## Version: $Id: Makefile,v 0.0 2007/08/30 03:04:12 yzf Exp $
## Keywords: 
## X-URL: 
all: SystemMonitor

JAVAC=javac
JAVA=java
ICE_CLASSPATH=../../../thirdparty/lib/java/Ice-3.1.1.jar
CLASSPATH=${ICE_CLASSPATH}:MasterService.jar:.

MasterService.jar:
	${JAVAC} -cp ${ICE_CLASSPATH} ../../ice/java/ice-3.1.1/tfs/slice/*.java
	jar cvf $@ -C ../../ice/java/ice-3.1.1 tfs/slice/

SystemMonitor: SystemMonitor.java MasterService.jar
	${JAVAC} -cp ${CLASSPATH} SystemMonitor.java

run:
	${JAVA} -cp ${CLASSPATH} SystemMonitor
### Makefile ends here
