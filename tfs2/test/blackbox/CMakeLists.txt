# ================================================================ 
# testing
# ================================================================

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

    WRITE_FILE(CMakeTFS.log "PARTS:${PARTS}" APPEND)
    
    #ADD_EXECUTABLE(${NAME} ${PARTS} ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_WE}.cpp)
    #ADD_EXECUTABLE(${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_WE}.cpp ${PARTS} )
    ADD_EXECUTABLE(${NAME} ${PARTS} )
    
    ADD_TEST(${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${NAME})
    
  ENDIF(PYTHONINTERP_FOUND)
ENDMACRO(ADD_CXXTEST)

#===============================================================================================
# Testing
#===============================================================================================

SET(CMAKE_BUILD_TYPE Debug)

AUX_SOURCE_DIRECTORY(../ice/c++/ice-${ICE_VERSION} ICESRC)

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_FILE_OFFSET_BITS=64")
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_FILE_OFFSET_BITS=64")
SET(CMAKE_BUILD_TYPE Debug)

ADD_EXECUTABLE(test_append testappend/TestAppend.cpp tfs_test/Task.cpp tfs_test/TaskManager.cpp ${TFS_ROOT}/src/util/Thread.cpp ${TFS_ROOT}/src/util/Process.cpp)
TARGET_LINK_LIBRARIES(test_append tfs_client Ice ssl datatransfer pthread tfs_ice log4cplus rudeconfig)

ADD_EXECUTABLE(test_readcapacity testappend/TestReadCapacity.cpp tfs_test/Task.cpp tfs_test/TaskManager.cpp ${TFS_ROOT}/src/util/Thread.cpp ${TFS_ROOT}/src/util/Process.cpp)
TARGET_LINK_LIBRARIES(test_readcapacity tfs_client Ice ssl datatransfer pthread tfs_ice log4cplus rudeconfig)

ADD_EXECUTABLE(test_appendcapacity testappend/TestAppendCapacity.cpp tfs_test/Task.cpp tfs_test/TaskManager.cpp ${TFS_ROOT}/src/util/Thread.cpp ${TFS_ROOT}/src/util/Process.cpp)
TARGET_LINK_LIBRARIES(test_appendcapacity tfs_client Ice ssl rudeconfig datatransfer pthread tfs_ice log4cplus rudeconfig)

ADD_EXECUTABLE(test_taskmanager tfs_test/TestTaskManager.cpp tfs_test/Task.cpp tfs_test/TaskManager.cpp ${TFS_ROOT}/src/util/Thread.cpp ${TFS_ROOT}/src/util/Process.cpp)
TARGET_LINK_LIBRARIES(test_taskmanager pthread)

ADD_CXXTEST(test_file ${BLACKBOX_ROOT}/client/TestFile.hpp)
TARGET_LINK_LIBRARIES(test_file tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)

ADD_CXXTEST(test_fs ${BLACKBOX_ROOT}/client/TestFileSystem.hpp)
TARGET_LINK_LIBRARIES(test_fs tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)

ADD_CXXTEST(test_stream ${BLACKBOX_ROOT}/client/TestStream.hpp)
TARGET_LINK_LIBRARIES(test_stream tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)

ADD_EXECUTABLE(test_operation client/TestOperation.cpp)
TARGET_LINK_LIBRARIES(test_operation tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)

ADD_EXECUTABLE(test_basic client/TestBasic.cpp)
TARGET_LINK_LIBRARIES(test_basic tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)

ADD_EXECUTABLE(test_buffer client/TestBuffer.cpp)
TARGET_LINK_LIBRARIES(test_buffer tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)

ADD_EXECUTABLE(test_text client/TestText.cpp)
TARGET_LINK_LIBRARIES(test_text tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)
