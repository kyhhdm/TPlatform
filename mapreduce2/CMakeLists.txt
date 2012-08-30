# Sets the name of the project. This creates the variables projectname_BINARY_DIR and projectname_SOURCE_DIR.
PROJECT (mapreduce)

# Enviroment detection
IF (WIN32)
	SET(GCC_VERSION 4.1)
	SET(ICE_VERSION 3.1.1)
	SET(THIRDPARTY_LIB_PATH vc8)
	SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall ")
	SET(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -Wall ")
	
	#setup 
	INCLUDE_DIRECTORIES ("C:\\boost_1_34_1")
ELSE (WIN32)
	EXEC_PROGRAM(gcc ARGS "-dumpversion | grep -o \"^[0-9]\\.[0-9]\" - " OUTPUT_VARIABLE GCC_VERSION)
	EXEC_PROGRAM(grep ARGS "-o \"[0-9]\\.[0-9]\\.[0-9]\" ../../thirdparty/include/Ice/Current.h" OUTPUT_VARIABLE ICE_VERSION)
	SET(THIRDPARTY_LIB_PATH gcc-${GCC_VERSION})
	SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter")
	SET(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter")
	# for gcov
	#SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -fprofile-arcs -ftest-coverage")
	#SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "-fprofile-arcs -ftest-coverage")
ENDIF (WIN32)

MESSAGE(STATUS "thirdparty path : ${THIRDPARTY_LIB_PATH}")
MESSAGE(STATUS "ice version : ${ICE_VERSION}")

# Flags for Build Type 
SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)
#INCLUDE(CMakePrintSystemInformation)

# Path variables, change them if you move this file or change layout of the repository
SET(TPLATFORM_ROOT ${PROJECT_SOURCE_DIR}/..)
SET(THIRD_PARTY_ROOT ${TPLATFORM_ROOT}/thirdparty)
SET(MAPREDUCE_ROOT ${PROJECT_SOURCE_DIR})
SET(MODULE_ICE_ROOT ${MAPREDUCE_ROOT}/src/ice/c++/ice-${ICE_VERSION})
SET(MODULE_MST_ROOT ${MAPREDUCE_ROOT}/src/master)
SET(MODULE_WKR_ROOT ${MAPREDUCE_ROOT}/src/worker)
SET(MODULE_CLT_ROOT ${MAPREDUCE_ROOT}/src/client)
SET(MODULE_APP_ROOT ${MAPREDUCE_ROOT}/src/app)
SET(MONITOR_ROOT ${MAPREDUCE_ROOT}/src/monitor)
SET(TEST_ROOT ${MAPREDUCE_ROOT}/test)

# For debug purpose
MESSAGE(STATUS "TPLATFORM_ROOT:${TPLATFORM_ROOT}")
MESSAGE(STATUS "THIRD_PARTY_ROOT:${THIRD_PARTY_ROOT}")
MESSAGE(STATUS "MAPREDUCE_ROOT:${MAPREDUCE_ROOT}")
MESSAGE(STATUS "TEST_ROOT:${TEST_ROOT}")
MESSAGE(STATUS "MODULE_ICE_ROOT:${MODULE_ICE_ROOT}")
MESSAGE(STATUS "MODULE_MST_ROOT:${MODULE_MST_ROOT}")
MESSAGE(STATUS "MODULE_WKR_ROOT:${MODULE_WKR_ROOT}")
MESSAGE(STATUS "MODULE_CLT_ROOT:${MODULE_CLT_ROOT}")
MESSAGE(STATUS "MODULE_APP_ROOT:${MODULE_APP_ROOT}")
MESSAGE(STATUS "MONITOR_ROOT:${MONITOR_ROOT}")

# Add include directories to the build.
INCLUDE_DIRECTORIES (${MAPREDUCE_ROOT}/src)
INCLUDE_DIRECTORIES (${MODULE_ICE_ROOT})
INCLUDE_DIRECTORIES (${MODULE_CLT_ROOT}/)
INCLUDE_DIRECTORIES (${THIRD_PARTY_ROOT}/include)
#INCLUDE_DIRECTORIES (${TPLATFORM_ROOT}/tfs/ice/c++/ice-3.1.1/)

# Specify directories in which to search for libraries.
LINK_DIRECTORIES(${THIRD_PARTY_ROOT}/lib/${THIRDPARTY_LIB_PATH})
MESSAGE(STATUS "LINK_DIRECTORIES: ${THIRD_PARTY_ROOT}/lib/${THIRDPARTY_LIB_PATH}")

# Collects the names of all the source files in the specified directory and stores the list in the variable provided.
AUX_SOURCE_DIRECTORY(src/master SRC_MASTER)
AUX_SOURCE_DIRECTORY(src/worker SRC_WORKER)
AUX_SOURCE_DIRECTORY(src/client SRC_CLIENT)
AUX_SOURCE_DIRECTORY(src/client/mapred SRC_CLIENT_INTERFACE)
AUX_SOURCE_DIRECTORY(src/ice/c++/ice-${ICE_VERSION} SRC_ICE)
#MESSAGE(STATUS "SRC_ICE:${SRC_ICE}")


# ================================================================ 
# build libararies
# ================================================================ 
ADD_LIBRARY(mapred_ice STATIC ${SRC_ICE})
ADD_LIBRARY(mapred_client STATIC ${SRC_CLIENT} ${MODULE_ICE_ROOT}/JobService.cpp ${MODULE_ICE_ROOT}/JobDetail.cpp ${MODULE_ICE_ROOT}/MapReduceJob.cpp)
TARGET_LINK_LIBRARIES(mapred_client Ice)
ADD_LIBRARY(mapred_interface STATIC ${SRC_CLIENT_INTERFACE})
TARGET_LINK_LIBRARIES(mapred_interface twreader query segtag util dl boost_filesystem z tfs_client log4cplus Ice rudeconfig datatransfer tfs_ice)


# ================================================================ 
# build executables
# ================================================================ 
ADD_EXECUTABLE(mapred_master ${SRC_MASTER})
TARGET_LINK_LIBRARIES(mapred_master mapred_ice log4cplus Ice rudeconfig tfs_mapred tfs_client tfs_ice datatransfer Ice)
ADD_EXECUTABLE(mapred_monitor ${MONITOR_ROOT}/cppmonitor/Monitor.cpp)
TARGET_LINK_LIBRARIES(mapred_monitor mapred_ice Ice rudeconfig)

# worker
ADD_EXECUTABLE(mapred_worker ${SRC_WORKER})
TARGET_LINK_LIBRARIES(mapred_worker mapred_ice   mapred_interface)
ADD_EXECUTABLE(mapred_mapper src/worker/taskRunner/Mapper.cpp)
TARGET_LINK_LIBRARIES(mapred_mapper   mapred_interface)
ADD_EXECUTABLE(mapred_reducer src/worker/taskRunner/Reducer.cpp)
TARGET_LINK_LIBRARIES(mapred_reducer   mapred_interface)

ADD_EXECUTABLE(mapred_serial ${MAPREDUCE_ROOT}/src/sversion/SMapReduce.cpp)
TARGET_LINK_LIBRARIES(mapred_serial mapred_interface mapred_client Ice rudeconfig boost_filesystem dl)

# ================================================================ 
# install#
# ================================================================
INCLUDE(CMakeLists.install)

# ================================================================ 
# applications
# ================================================================
ADD_SUBDIRECTORY(src/app)

# ================================================================ 
# unit testing
# ================================================================
ADD_SUBDIRECTORY(test/unit)
ADD_SUBDIRECTORY(test/blackbox)

