### Makefile --- 

## Author: yzf@net.pku.edu.cn
## Version: $Id: Makefile,v 0.0 2007/08/31 02:20:49 yzf Exp $
## Keywords: 
## X-URL: 

JAVAC=javac
JAVA=java

THIRDPARTY_PATH=../../../thirdparty
LIBGWT_PATH=${THIRDPARTY_PATH}/gwt-linux-1.4.60
LIBICE_PATH=${THIRDPARTY_PATH}/lib/java
CLASSPATH=./src:./classes:${LIBGWT_PATH}/gwt-user.jar:${LIBGWT_PATH}/gwt-dev-linux.jar:${LIBICE_PATH}/Ice-3.1.1.jar:./lib/MasterService.jar

WEBMONITOR_INSTALL_PATH=/var/lib/tomcat5/webapps/tfs-monitor

.PHONY: shell webclient server install
all: server webclient

lib/MasterService.jar:
	${JAVAC} -cp ${LIBICE_PATH}/Ice-3.1.1.jar ../../ice/java/ice-3.1.1/tfs/slice/*.java
	jar cvf $@ -C ../../ice/java/ice-3.1.1 tfs/slice/

shell: server
	${JAVA} -cp ${CLASSPATH} com.google.gwt.dev.GWTShell -out ./www tfs.SystemMonitor/SystemMonitor.html

webclient:
	${JAVA} -cp ${CLASSPATH} -Djava.awt.headless=true com.google.gwt.dev.GWTCompiler -out ./www tfs.SystemMonitor

server: lib/MasterService.jar
	${JAVAC} -classpath ${CLASSPATH} -d classes ./src/tfs/server/MonitorServiceImpl.java

install:
	mkdir -p ${WEBMONITOR_INSTALL_PATH}/WEB-INF/classes/ ${WEBMONITOR_INSTALL_PATH}/WEB-INF/lib/
	cp -rf src/tfs/web.xml ${WEBMONITOR_INSTALL_PATH}/WEB-INF/
	cp -rf classes/tfs ${WEBMONITOR_INSTALL_PATH}/WEB-INF/classes/
	cp -rf ../../ice/java/ice-3.1.1/tfs ${WEBMONITOR_INSTALL_PATH}/WEB-INF/classes/
	cp -rf ${LIBICE_PATH}/Ice-3.1.1.jar lib/gwt-user-crop.jar lib/MasterService.jar ${WEBMONITOR_INSTALL_PATH}/WEB-INF/lib/
	cp -rf www/tfs.SystemMonitor/* ${WEBMONITOR_INSTALL_PATH}/
### Makefile ends here
