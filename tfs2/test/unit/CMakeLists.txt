# ================================================================ 
# testing
# ================================================================
INCLUDE(CTest)
# Make sure testing is enabled
ENABLE_TESTING()

# Use Python interpreter
FIND_PACKAGE(PythonInterp)

# Path to the cxxtestgen.py script
SET(CXXTESTGEN ${THIRD_PARTY_ROOT}/cxxtest/cxxtestgen.py)

# This macro simplifies the inclusion of tests written using the CxxTest
MACRO(ADD_CXXTEST NAME)
  IF(PYTHONINTERP_FOUND)
    # clean PARTS
    SET(PARTS)
    # generate the parts
    FOREACH(_PART ${ARGN})
      #GET_FILENAME_COMPONENT(_NAME ${_PART} NAME)
      GET_FILENAME_COMPONENT(_PATH ${_PART} PATH)
      GET_FILENAME_COMPONENT(_NAME_WE ${_PART} NAME_WE)
      GET_FILENAME_COMPONENT(_EXT ${_PART} EXT)

      IF(_EXT STREQUAL ".cpp")
	  # get cpp files to be linked
	    SET(PARTS ${PARTS} ${_PART})
      ELSEIF(_EXT STREQUAL ".hpp")
	    ADD_CUSTOM_COMMAND(
          OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_WE}.cpp
          COMMAND
          ${PYTHON_EXECUTABLE} ${CXXTESTGEN}
          --part
          -o ${_NAME_WE}.cpp
          ${_PART}
          DEPENDS ${_PART}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	    )
	    # get generated cpp files
		#MESSAGE("generate ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_WE}.cpp")
	    #SET(PARTS ${PARTS} ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_WE}.cpp)
	    SET(PARTS ${PARTS} ${_NAME_WE}.cpp)
      ENDIF(_EXT STREQUAL ".cpp")
    ENDFOREACH(_PART)

    # generate the runner
    ADD_CUSTOM_COMMAND(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_runner.cpp
      COMMAND
      ${PYTHON_EXECUTABLE} ${CXXTESTGEN}
      --runner=ErrorPrinter --root
      -o ${NAME}_runner.cpp
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      )
	#MESSAGE("generate ${NAME}_runner.cpp")
    SET(PARTS ${PARTS} ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_runner.cpp)

    #WRITE_FILE(CMakeTFS.log "PARTS:${PARTS}" APPEND)
    
    #ADD_EXECUTABLE(${NAME} ${PARTS} ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_WE}.cpp)
    #ADD_EXECUTABLE(${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_WE}.cpp ${PARTS} )
    ADD_EXECUTABLE(${NAME} ${PARTS} )
    
    ADD_TEST(${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${NAME})
    
  ENDIF(PYTHONINTERP_FOUND)
ENDMACRO(ADD_CXXTEST)

#===============================================================================================
# Testing
#===============================================================================================
LINK_LIBRARIES(log4cplus Ice rudeconfig)

ADD_CXXTEST(testCxxTest ${TEST_ROOT}/TestCxxTest.hpp)

#----------------------------------------------------------------------------------------------
# ChunkServer Testing
#---------------------------------------------------------------------------------------------
#ADD_CXXTEST(testChunkManager ${UNITTEST_ROOT}/chunkserver/TestChunkManager.hpp 
#            ${MODULE_CSV_ROOT}/ChunkManager.cpp ${MODULE_CSV_ROOT}/ChunkServerConf.cpp 
#	     ${MODULE_CSV_ROOT}/FileUtil.cpp
#            ${MODULE_CSV_ROOT}/FileSystemUtil.cpp ${MODULE_CSV_ROOT}/DiskManager.cpp  
#	     ${MODULE_CSV_ROOT}/DiskUtil.cpp
#            )
#TARGET_LINK_LIBRARIES(testChunkManager  datatransfer tfs_ice log4cplus Ice rudeconfig 
#	     boost_thread boost_filesystem)

ADD_CXXTEST(testDiskManager ${UNITTEST_ROOT}/chunkserver/TestDiskManager.hpp
            ${MODULE_CSV_ROOT}/DiskManager.cpp ${MODULE_CSV_ROOT}/ChunkServerConf.cpp 
            ${MODULE_CSV_ROOT}/FileUtil.cpp
            ${MODULE_CSV_ROOT}/FileSystemUtil.cpp  ${MODULE_CSV_ROOT}/DiskUtil.cpp
            )
TARGET_LINK_LIBRARIES(testDiskManager  datatransfer tfs_ice log4cplus Ice rudeconfig 
	boost_thread boost_filesystem)


ADD_CXXTEST(testRemoteDealer ${UNITTEST_ROOT}/chunkserver/TestRemoteDealer.hpp
            )
TARGET_LINK_LIBRARIES(testRemoteDealer  datatransfer tfs_ice log4cplus Ice rudeconfig boost_thread)

ADD_CXXTEST(testLocalAppend ${UNITTEST_ROOT}/chunkserver/TestLocalAppend.hpp
            )
TARGET_LINK_LIBRARIES(testLocalAppend  datatransfer tfs_ice log4cplus Ice rudeconfig boost_thread)

ADD_CXXTEST(testFileUtil ${UNITTEST_ROOT}/chunkserver/TestFileUtil.hpp ${MODULE_CSV_ROOT}/FileUtil.cpp
            )
TARGET_LINK_LIBRARIES(testFileUtil  tfs_ice log4cplus Ice rudeconfig boost_thread)

ADD_CXXTEST(testFileSystemUtil ${UNITTEST_ROOT}/chunkserver/TestFileSystemUtil.hpp 
	${MODULE_CSV_ROOT}/FileSystemUtil.cpp
            )
TARGET_LINK_LIBRARIES(testFileSystemUtil  tfs_ice log4cplus Ice rudeconfig boost_thread boost_filesystem)

#----------------------------------------------------------------------------------------------
# Master Test 
#----------------------------------------------------------------------------------------------
ADD_CXXTEST(testActiveChunkManager ${UNITTEST_ROOT}/master/TestActiveChunkManager.hpp 
    	${MODULE_MST_ROOT}/ActiveChunkManager.cpp ${MODULE_ICE_ROOT}/Exceptions.cpp 
    	${MODULE_ICE_ROOT}/Address.cpp)

ADD_CXXTEST(testChunkServerManager ${UNITTEST_ROOT}/master/TestChunkServerManager.hpp 
    	${MODULE_MST_ROOT}/ChunkServerManager.cpp ${MODULE_ICE_ROOT}/Exceptions.cpp 
    	${MODULE_ICE_ROOT}/Address.cpp ${MODULE_ICE_ROOT}/Chunk.cpp)

ADD_CXXTEST(testClientManager ${UNITTEST_ROOT}/master/TestClientManager.hpp 
	${MODULE_MST_ROOT}/ClientManager.cpp ${MODULE_ICE_ROOT}/Exceptions.cpp 
	${MODULE_ICE_ROOT}/Address.cpp)

#----------------------------------------------------------------------------------------------
# FsDirectory Test
#----------------------------------------------------------------------------------------------
ADD_CXXTEST(testFsDirectory ${UNITTEST_ROOT}/fsdirectory/TestFsDirectory.hpp)
TARGET_LINK_LIBRARIES(testFsDirectory tfs_fsdirectory tfs_ice log4cplus rudeconfig 
	boost_serialization boost_filesystem)

ADD_CXXTEST(testChunkTable ${UNITTEST_ROOT}/fsdirectory/TestChunkTable.hpp
    ${MODULE_FSD_ROOT}/ChunkTable.cpp 
    ${MODULE_ICE_ROOT}/Exceptions.cpp ${MODULE_MST_ROOT}/MasterConfig.cpp)

ADD_CXXTEST(testNewChunkTable ${UNITTEST_ROOT}/fsdirectory/TestNewChunkTable.hpp
    ${MODULE_FSD_ROOT}/NewChunkTable.cpp 
    ${MODULE_ICE_ROOT}/Exceptions.cpp ${MODULE_FSD_ROOT}/Path.cpp ${MODULE_MST_ROOT}/MasterConfig.cpp)


ADD_CXXTEST(testDirTree ${UNITTEST_ROOT}/fsdirectory/TestDirTree.hpp )
TARGET_LINK_LIBRARIES(testDirTree tfs_fsdirectory tfs_ice rudeconfig boost_serialization)

ADD_CXXTEST(testDirTreePath ${UNITTEST_ROOT}/fsdirectory/TestDirTreePath.hpp 
	${MODULE_ICE_ROOT}/Exceptions.cpp ${MODULE_FSD_ROOT}/DirTree.cpp ${MODULE_FSD_ROOT}/DirNode.cpp 
	${MODULE_FSD_ROOT}/Path.cpp ${MODULE_FSD_ROOT}/INode.cpp ${MODULE_FSD_ROOT}/DirTreePath.cpp 
	${MODULE_MST_ROOT}/MasterConfig.cpp)

ADD_CXXTEST(testFsLog ${UNITTEST_ROOT}/fsdirectory/TestFsLog.hpp
    ${MODULE_ICE_ROOT}/Exceptions.cpp ${MODULE_FSD_ROOT}/FsLog.cpp )

ADD_CXXTEST(testFsJournalManager ${UNITTEST_ROOT}/fsdirectory/TestFsJournalManager.hpp) 
TARGET_LINK_LIBRARIES(testFsJournalManager tfs_fsdirectory tfs_ice log4cplus rudeconfig 
	boost_serialization boost_filesystem)

ADD_CXXTEST(testLockTable ${UNITTEST_ROOT}/fsdirectory/TestLockTable.hpp
    ${MODULE_FSD_ROOT}/LockTable.cpp ${MODULE_ICE_ROOT}/Exceptions.cpp)

ADD_CXXTEST(testPath ${UNITTEST_ROOT}/fsdirectory/TestPath.hpp ${MODULE_FSD_ROOT}/Path.cpp)

#----------------------------------------------------------------------------------------------
# Application Test
#----------------------------------------------------------------------------------------------
#ADD_EXECUTABLE(rltest ${UNITTEST_ROOT}/shell/rltest.c) 
#TARGET_LINK_LIBRARIES(rltest readline history termcap)

ADD_CXXTEST(testCommandManager ${UNITTEST_ROOT}/shell/TestCommandManager.hpp ${SHELL_ROOT}/src/CommandManager.cpp )

ADD_CXXTEST(testFilePath ${UNITTEST_ROOT}/shell/TestFilePath.hpp ${SHELL_ROOT}/src/FilePath.cpp )


#----------------------------------------------------------------------------------------------
# Utility Test
#----------------------------------------------------------------------------------------------
ADD_EXECUTABLE(testThread ${UNITTEST_ROOT}/util/TestThread.cpp   ${TFS_ROOT}/src/util/Thread.cpp)
ADD_EXECUTABLE(testProcess ${UNITTEST_ROOT}/util/TestProcess.cpp  ${TFS_ROOT}/src/util/Process.cpp)
