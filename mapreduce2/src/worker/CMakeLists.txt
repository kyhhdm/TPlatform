INCLUDE_DIRECTORIES(${MODULE_WKR_ROOT}/include)

SET(ENV{LD_LIBRARY_PATH} ${MAPREDUCE_ROOT}/build/src/app/)
MESSAGE(STATUS "LD dir: $ENV{LD_LIBRARY_PATH}")


#ADD_EXECUTABLE(simple_client ${MODULE_WKR_ROOT}/src/simple_client.cpp)
#TARGET_LINK_LIBRARIES(simple_client classloader dl)

