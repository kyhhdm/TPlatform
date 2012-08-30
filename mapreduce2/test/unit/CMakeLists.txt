#================================================================ 
# testing
# ================================================================
INCLUDE_DIRECTORIES(${MODULE_CLT_ROOT}/mapred)
INCLUDE_DIRECTORIES(${MODULE_WKR_ROOT})
INCLUDE_DIRECTORIES(${MODULE_APP_ROOT})
INCLUDE_DIRECTORIES(${THIRD_PARTY_ROOT}/include)
SET(INTERFACE_ROOT ${MODULE_CLT_ROOT}/mapred)
SET(UNITTEST_ROOT ${TEST_ROOT}/unit)

# Make sure testing is enabled
ENABLE_TESTING()
INCLUDE(CTest)

# Use Python interpreter
FIND_PACKAGE(PythonInterp)

# Path to the cxxtestgen.py script
SET(CXXTESTGEN ${THIRD_PARTY_ROOT}/cxxtest/cxxtestgen.py)

# This macro simplifies the inclusion of tests written using the CxxTest
MACRO(ADD_CXXTEST NAME)
  ADD_DEFINITIONS(-DCXX_TEST)  
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

#===============================================================================================
# Testing interface
#===============================================================================================
LINK_LIBRARIES(boost_filesystem dl)

ADD_CXXTEST(testFileStream ${UNITTEST_ROOT}/mapred/TestFileStream.hpp 
${INTERFACE_ROOT}/FileStreamLocal.cpp
#${INTERFACE_ROOT}/FileStreamTfs.cpp
)
#TARGET_LINK_LIBRARIES(testFileStream boost_filesystem)

ADD_CXXTEST(testArchiveBuffer ${UNITTEST_ROOT}/mapred/TestArchiveBuffer.hpp 
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
)

ADD_CXXTEST(testArchive ${UNITTEST_ROOT}/mapred/TestArchive.hpp 
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
)

ADD_CXXTEST(testClassLoader ${UNITTEST_ROOT}/mapred/TestClassLoader.hpp 
${INTERFACE_ROOT}/ClassLoader.cpp
)

ADD_LIBRARY(SimpleDll SHARED
${UNITTEST_ROOT}/mapred/SimpleDll.cpp
${INTERFACE_ROOT}/ClassLoader.cpp
)
TARGET_LINK_LIBRARIES(SimpleDll)

ADD_CXXTEST(testTKeyValue ${UNITTEST_ROOT}/mapred/TestTKeyValue.hpp 
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
)

ADD_CXXTEST(testTaskConfigure ${UNITTEST_ROOT}/mapred/TestTaskConfigure.hpp 
${INTERFACE_ROOT}/TaskConfigure.cpp
)

#ADD_CXXTEST(testHashableComparable ${UNITTEST_ROOT}/mapred/TestHashableComparable.hpp 
#)

ADD_LIBRARY(MapReduceDll SHARED
${UNITTEST_ROOT}/mapred/MapReduceDll.cpp
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
)
TARGET_LINK_LIBRARIES(MapReduceDll)


ADD_CXXTEST(testPartitioner ${UNITTEST_ROOT}/mapred/TestPartitioner.hpp 
${INTERFACE_ROOT}/Partitioner.cpp
${INTERFACE_ROOT}/TaskConfigure.cpp
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
${INTERFACE_ROOT}/FileStreamLFS.cpp
${INTERFACE_ROOT}/ClassLoader.cpp
)

ADD_CXXTEST(testSorter ${UNITTEST_ROOT}/mapred/TestSorter.hpp 
${INTERFACE_ROOT}/Sorter.cpp
${INTERFACE_ROOT}/Partitioner.cpp
${INTERFACE_ROOT}/TaskConfigure.cpp
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
${INTERFACE_ROOT}/FileStreamLFS.cpp
${INTERFACE_ROOT}/ClassLoader.cpp
)

ADD_CXXTEST(testSetMapper ${UNITTEST_ROOT}/mapred/TestSetMapper.hpp 
${INTERFACE_ROOT}/SetMapper.cpp
${INTERFACE_ROOT}/Partitioner.cpp
${INTERFACE_ROOT}/TaskConfigure.cpp
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
${INTERFACE_ROOT}/FileStreamLFS.cpp
${INTERFACE_ROOT}/ClassLoader.cpp
)
TARGET_LINK_LIBRARIES(testSetMapper log4cplus)

ADD_CXXTEST(testKeyValuePool ${UNITTEST_ROOT}/mapred/TestKeyValuePool.hpp 
${INTERFACE_ROOT}/KeyValuePool.cpp
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
)

#ADD_CXXTEST(testMock  ${TEST_ROOT}/TestRandom.hpp
#${TEST_ROOT}/mock_time.cpp
#${TEST_ROOT}/code.cpp
#)
#ADD_CXXTEST(testSetReducer ${UNITTEST_ROOT}/mapred/TestSetReducer.hpp 
#${INTERFACE_ROOT}/SetReducer.cpp
#${INTERFACE_ROOT}/KeyValuePool.cpp
#${INTERFACE_ROOT}/DirectCollector.cpp
#${INTERFACE_ROOT}/TaskConfigure.cpp
#${INTERFACE_ROOT}/Sorter.cpp
#${INTERFACE_ROOT}/Partitioner.cpp
#${INTERFACE_ROOT}/Archive.cpp
#${INTERFACE_ROOT}/ArchiveBuffer.cpp
#${INTERFACE_ROOT}/FileStreamLocal.cpp
#${INTERFACE_ROOT}/ClassLoader.cpp
#)
#TARGET_LINK_LIBRARIES(testSetReducer log4cplus)

ADD_CXXTEST(testPageRank ${UNITTEST_ROOT}/PageRank/TestPageRank.hpp 
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/TianwangRawFileFeeder.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
${MODULE_APP_ROOT}/PageRank/PageRankValue.cpp
)
TARGET_LINK_LIBRARIES(testPageRank mapred_interface)

ADD_CXXTEST(testPageRank2 ${UNITTEST_ROOT}/PageRank2/TestPageRank2.hpp 
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/TianwangRawFileFeeder.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
${MODULE_APP_ROOT}/PageRank2/PageRankValue.cpp
)
TARGET_LINK_LIBRARIES(testPageRank2 mapred_interface)

ADD_CXXTEST(testPageRank3 ${UNITTEST_ROOT}/PageRank3/TestPageRank3.hpp 
${INTERFACE_ROOT}/Archive.cpp
${INTERFACE_ROOT}/ArchiveBuffer.cpp
${INTERFACE_ROOT}/TianwangRawFileFeeder.cpp
${INTERFACE_ROOT}/FileStreamLocal.cpp
${MODULE_APP_ROOT}/PageRank3/PageRankValue.cpp
)
TARGET_LINK_LIBRARIES(testPageRank3 mapred_interface)

ADD_EXECUTABLE(testReg ${UNITTEST_ROOT}/PageRank/TestReg.cpp)
TARGET_LINK_LIBRARIES(testReg boost_regex)
