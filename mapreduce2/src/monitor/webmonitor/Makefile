### Makefile --- 

## Author: yzf@net.pku.edu.cn
## Version: $Id: Makefile,v 0.0 2007/08/31 02:20:49 yzf Exp $
## Keywords: 
## X-URL: 

# you make change the install path before running `make install'
WEBAPP_NAME=mapred-monitor
WEBAPP_INSTALL_PATH=/var/lib/tomcat5/webapps/${WEBAPP_NAME}

JAVAC=javac
JAVA=java
JAR=jar 

THIRDPARTY_PATH=../../../../thirdparty
LIBGWT_PATH=${THIRDPARTY_PATH}/gwt-linux-1.4.60
LIBICE_PATH=${THIRDPARTY_PATH}/lib/java
CLASSPATH=./src:./classes:${LIBGWT_PATH}/gwt-user.jar:${LIBGWT_PATH}/gwt-dev-linux.jar:${LIBICE_PATH}/Ice-3.1.1.jar:./lib/jfreechart-1.0.8.jar:./lib/jcommon-1.0.12.jar:./lib/MonitorService.jar

.PHONY: shell webclient server install
all: MonitorService.jar server webclient 

MonitorService.jar:
	${JAVAC} -cp ${LIBICE_PATH}/Ice-3.1.1.jar ../../ice/java/ice-3.1.1/mapreduce/slice/*.java
	${JAR} cvf lib/$@ -C ../../ice/java/ice-3.1.1 mapreduce/slice/

shell: server
	${JAVA} -cp ${CLASSPATH} com.google.gwt.dev.GWTShell -out ./www mapreduce.WebMonitor/WebMonitor.html

webclient:
	${JAVA} -cp ${CLASSPATH} -Djava.awt.headless=true com.google.gwt.dev.GWTCompiler -out ./www mapreduce.WebMonitor

server: src/mapreduce/server/ChartGeneratorImpl.java src/mapreduce/server/MonitorServiceImpl.java
	${JAVAC} -classpath ${CLASSPATH} -d classes $^

install:
	mkdir -p ${WEBAPP_INSTALL_PATH}/WEB-INF/classes/ ${WEBAPP_INSTALL_PATH}/WEB-INF/lib/
	cp -rf src/mapreduce/web.xml ${WEBAPP_INSTALL_PATH}/WEB-INF/
	cp -rf classes/mapreduce ${WEBAPP_INSTALL_PATH}/WEB-INF/classes/
	cp -rf ${LIBICE_PATH}/Ice-3.1.1.jar lib/* ${WEBAPP_INSTALL_PATH}/WEB-INF/lib/
	cp -rf www/mapreduce.WebMonitor/* ${WEBAPP_INSTALL_PATH}/
### Makefile ends here
