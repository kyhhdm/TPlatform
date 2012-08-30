#================================================================ 
# testing
# ================================================================
INCLUDE_DIRECTORIES(${MODULE_CLT_ROOT}/mapred)
INCLUDE_DIRECTORIES(${MODULE_WKR_ROOT})
INCLUDE_DIRECTORIES(${MODULE_APP_ROOT})
INCLUDE_DIRECTORIES(${THIRD_PARTY_ROOT}/include)

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
SET(INTERFACE_ROOT ${MODULE_CLT_ROOT}/mapred)

#===============================================================================================
# Testing 
#===============================================================================================
