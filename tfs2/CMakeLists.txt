# Sets the name of the project. This creates the variables projectname_BINARY_DIR and projectname_SOURCE_DIR.
PROJECT (tfs)

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
ENDIF (WIN32)
MESSAGE(STATUS "thirdparty path : ${THIRDPARTY_LIB_PATH}")
MESSAGE(STATUS "ice version : ${ICE_VERSION}")

# Set Build Type Debug/Release
SET(CMAKE_BUILD_TYPE Debug)
#INCLUDE(CMakePrintSystemInformation)

# Path variables, change them if you move this file or change layout of the repository
SET(TPLATFORM_ROOT ${PROJECT_SOURCE_DIR}/..)
SET(TFS_ROOT ${PROJECT_SOURCE_DIR})
SET(MODULE_ICE_ROOT ${TFS_ROOT}/src/ice/c++/ice-${ICE_VERSION})
SET(MODULE_MST_ROOT ${TFS_ROOT}/src/master)
SET(MODULE_FSD_ROOT ${TFS_ROOT}/src/fsdirectory)
SET(MODULE_TRANS_ROOT ${TFS_ROOT}/src/datatransfer)
SET(MODULE_CSV_ROOT ${TFS_ROOT}/src/chunkserver)
SET(MODULE_CLT_ROOT ${TFS_ROOT}/src/client)
SET(MODULE_APP_ROOT ${TFS_ROOT}/src/app)
SET(MONITOR_ROOT ${TFS_ROOT}/src/monitor)
SET(SHELL_ROOT ${TFS_ROOT}/src/app/shell)

SET(TEST_ROOT ${TFS_ROOT}/test)
SET(UNITTEST_ROOT ${TEST_ROOT}/unit)
SET(BLACKBOX_ROOT ${TEST_ROOT}/blackbox)
SET(THIRD_PARTY_ROOT ${TPLATFORM_ROOT}/thirdparty)

# For debug purpose
MESSAGE(STATUS "TPLATFORM_ROOT:${TPLATFORM_ROOT}")
MESSAGE(STATUS "TFS_ROOT:${TFS_ROOT}")
MESSAGE(STATUS "TEST_ROOT:${TEST_ROOT}")
MESSAGE(STATUS "MODULE_ICE_ROOT:${MODULE_ICE_ROOT}")
MESSAGE(STATUS "MODULE_MST_ROOT:${MODULE_MST_ROOT}")
MESSAGE(STATUS "MODULE_CSV_ROOT:${MODULE_CSV_ROOT}")
MESSAGE(STATUS "MODULE_CLT_ROOT:${MODULE_CLT_ROOT}")
MESSAGE(STATUS "MODULE_APP_ROOT:${MODULE_APP_ROOT}")
MESSAGE(STATUS "THIRD_PARTY_ROOT:${THIRD_PARTY_ROOT}")
MESSAGE(STATUS "MONITOR_ROOT:${MONITOR_ROOT}")

# Add include directories to the build.
INCLUDE_DIRECTORIES (${TFS_ROOT}/src)
INCLUDE_DIRECTORIES (${MODULE_ICE_ROOT})
INCLUDE_DIRECTORIES (${MODULE_CSV_ROOT})
INCLUDE_DIRECTORIES (${MODULE_CLT_ROOT})
INCLUDE_DIRECTORIES (${THIRD_PARTY_ROOT}/include)

# Specify directories in which to search for libraries.
LINK_DIRECTORIES(${THIRD_PARTY_ROOT}/lib/${THIRDPARTY_LIB_PATH})
LINK_DIRECTORIES(${MODULE_CSV_ROOT}/datatransfer)


# Collects the names of all the source files in the specified directory and stores the list in the variable provided.
AUX_SOURCE_DIRECTORY(src/master SRC_MASTER)
AUX_SOURCE_DIRECTORY(src/chunkserver SRC_CHUNKSERVER)
AUX_SOURCE_DIRECTORY(src/datatransfer SRC_TRANS)
AUX_SOURCE_DIRECTORY(src/fsdirectory SRC_FSDIR)
AUX_SOURCE_DIRECTORY(src/client/tfs SRC_CLIENT)
AUX_SOURCE_DIRECTORY(src/mapred SRC_MAPRED)
AUX_SOURCE_DIRECTORY(src/ice/c++/ice-${ICE_VERSION} SRC_ICE)
#SET(SRC_FSDIR  ${SRC_FSDIR} master/MasterConfig.cpp)

#
# build libararies
#
ADD_LIBRARY(tfs_ice STATIC ${SRC_ICE})

ADD_LIBRARY(tfs_fsdirectory STATIC ${SRC_FSDIR} src/master/MasterConfig.cpp)

#ADD_LIBRARY(datatransfer STATIC ${SRC_TRANS})

ADD_LIBRARY(tfs_client STATIC ${SRC_CLIENT})

ADD_LIBRARY(tfs_mapred STATIC ${SRC_MAPRED} ${MODULE_ICE_ROOT}/ClientService.cpp ${MODULE_ICE_ROOT}/Chunk.cpp ${MODULE_ICE_ROOT}/Address.cpp ${MODULE_ICE_ROOT}/FileInfo.cpp ${MODULE_ICE_ROOT}/Exceptions.cpp)

#
# build executables
#
LINK_LIBRARIES(log4cplus Ice rudeconfig)

ADD_EXECUTABLE(tfs_master ${SRC_MASTER})
TARGET_LINK_LIBRARIES(tfs_master tfs_fsdirectory tfs_ice boost_serialization boost_filesystem)


ADD_EXECUTABLE(tfs_chunkserver ${SRC_CHUNKSERVER})
TARGET_LINK_LIBRARIES(tfs_chunkserver tfs_ice boost_thread pthread ssl boost_filesystem)


ADD_EXECUTABLE(tfs_monitor ${MONITOR_ROOT}/cppmonitor/SystemMonitor.cpp)
TARGET_LINK_LIBRARIES(tfs_monitor tfs_ice)


# ================================================================ 
# install#
# ================================================================
INCLUDE(CMakeLists.install)

# ================================================================ 
# sub dirs
# ================================================================
ADD_SUBDIRECTORY(src/app)
ADD_SUBDIRECTORY(test/unit)
ADD_SUBDIRECTORY(test/blackbox)
