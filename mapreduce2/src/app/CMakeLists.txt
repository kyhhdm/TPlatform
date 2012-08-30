INCLUDE_DIRECTORIES(${MODULE_CLT_ROOT})
INCLUDE_DIRECTORIES(${MODULE_CLT_ROOT}/mapred)
INCLUDE_DIRECTORIES(${THIRD_PARTY_ROOT}/include)


# app WordCnt
#ADD_LIBRARY(PennySort SHARED
#${MODULE_APP_ROOT}/PennySort2/PennySort.cpp
#${MODULE_APP_ROOT}/PennySort2/PennySortMapper.cpp
#${MODULE_APP_ROOT}/PennySort2/PennySortReducer.cpp
#${MODULE_APP_ROOT}/PennySort2/PennySortRecord.cpp
#)
#TARGET_LINK_LIBRARIES(PennySort mapred_interface)

#ADD_LIBRARY(PennySortSimple SHARED
#${MODULE_APP_ROOT}/PennySort2/PennySort.cpp
#${MODULE_APP_ROOT}/PennySort2/PennySortMapper.cpp
#${MODULE_APP_ROOT}/PennySort2/PennySortReducer.cpp
#${MODULE_APP_ROOT}/PennySort2/PennySortRecordSimple.cpp
#)
#TARGET_LINK_LIBRARIES(PennySortSimple mapred_interface)


ADD_LIBRARY(WordCount SHARED
${MODULE_APP_ROOT}/WordCount/WordCount.cpp
${MODULE_APP_ROOT}/WordCount/WordCountMapper.cpp
${MODULE_APP_ROOT}/WordCount/WordCountReducer.cpp
)
TARGET_LINK_LIBRARIES(WordCount mapred_interface)

#ADD_LIBRARY(PageLen SHARED
#${MODULE_APP_ROOT}/PageLen/PageLen.cpp
#${MODULE_APP_ROOT}/PageLen/PageLenMapper.cpp
#${MODULE_APP_ROOT}/PageLen/PageLenReducer.cpp
#)
#TARGET_LINK_LIBRARIES(PageLen mapred_interface)

ADD_LIBRARY(PageRank SHARED
${MODULE_APP_ROOT}/PageRank/PageRank.cpp
${MODULE_APP_ROOT}/PageRank/PageRankFirstMapper.cpp
${MODULE_APP_ROOT}/PageRank/PageRankLatterMapper.cpp
${MODULE_APP_ROOT}/PageRank/PageRankValue.cpp
${MODULE_APP_ROOT}/PageRank/PageRankReducer.cpp
)
TARGET_LINK_LIBRARIES(PageRank boost_regex mapred_interface )

ADD_LIBRARY(PageRank2 SHARED
${MODULE_APP_ROOT}/PageRank2/PageRank.cpp
${MODULE_APP_ROOT}/PageRank2/PageRankFirstMapper.cpp
${MODULE_APP_ROOT}/PageRank2/PageRankLatterMapper.cpp
${MODULE_APP_ROOT}/PageRank2/PageRankValue.cpp
${MODULE_APP_ROOT}/PageRank2/PageRankReducer.cpp
)
TARGET_LINK_LIBRARIES(PageRank2 boost_regex mapred_interface )

ADD_LIBRARY(PageRank3 SHARED
${MODULE_APP_ROOT}/PageRank3/PageRank.cpp
${MODULE_APP_ROOT}/PageRank3/PageRankMapper.cpp
${MODULE_APP_ROOT}/PageRank3/PageRankValue.cpp
${MODULE_APP_ROOT}/PageRank3/PageRankReducer.cpp
)
TARGET_LINK_LIBRARIES(PageRank3 mapred_interface )



#
#
# applications 
#
ADD_EXECUTABLE(test_wc
${MODULE_APP_ROOT}/WordCount/WordCountMain.cpp)
TARGET_LINK_LIBRARIES(test_wc mapred_interface boost_filesystem dl)

#ADD_EXECUTABLE(penny_sort
#${MODULE_APP_ROOT}/PennySort2/PennySortMain.cpp)
#TARGET_LINK_LIBRARIES(penny_sort mapred_interface)

ADD_EXECUTABLE(mapred_job ${MODULE_APP_ROOT}/MapRedJob/MapReduceJobMain.cpp)
TARGET_LINK_LIBRARIES(mapred_job mapred_interface mapred_client rudeconfig)

ADD_EXECUTABLE(pagerank
${MODULE_APP_ROOT}/PageRank/PageRankMain.cpp
${MODULE_APP_ROOT}/PageRank/PageRankValue.cpp)
TARGET_LINK_LIBRARIES(pagerank mapred_interface)

ADD_EXECUTABLE(pagerank_mapred
${MODULE_APP_ROOT}/PageRank2/PageRankParallel.cpp)
TARGET_LINK_LIBRARIES(pagerank_mapred mapred_interface mapred_client rudeconfig)

ADD_EXECUTABLE(pagerank2
${MODULE_APP_ROOT}/PageRank2/PageRankMain.cpp
${MODULE_APP_ROOT}/PageRank2/PageRankValue.cpp)
TARGET_LINK_LIBRARIES(pagerank2 mapred_interface)

ADD_EXECUTABLE(pagerank3
${MODULE_APP_ROOT}/PageRank3/PageRankMain.cpp
${MODULE_APP_ROOT}/PageRank3/PageRankValue.cpp)
TARGET_LINK_LIBRARIES(pagerank3 mapred_interface)

ADD_EXECUTABLE(pagerankReader
${MODULE_APP_ROOT}/PageRank3/PageRankValueReader.cpp
${MODULE_APP_ROOT}/PageRank3/PageRankValue.cpp)
TARGET_LINK_LIBRARIES(pagerankReader mapred_interface)

#
# start examples 
#
INCLUDE("./CMakeLists.examples.txt")

#
# install
#
INCLUDE("CMakeLists.install")
