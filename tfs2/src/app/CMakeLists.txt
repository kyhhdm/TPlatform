
AUX_SOURCE_DIRECTORY(../ice/c++/ice-${ICE_VERSION} ICESRC)

ADD_EXECUTABLE(tfs_journal journalexplorer/JournalExplorerMain.cpp)
	TARGET_LINK_LIBRARIES(tfs_journal tfs_fsdirectory tfs_ice rudeconfig 
	boost_serialization boost_filesystem)

ADD_EXECUTABLE(Raw2TFS migrate/Raw2Tfs.cpp)
TARGET_LINK_LIBRARIES(Raw2TFS tfs_client datatransfer tfs_ice twreader 
	log4cplus rudeconfig Ice z)


ADD_EXECUTABLE(word_creator WordCreator.cpp)
TARGET_LINK_LIBRARIES(word_creator tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig
	readline termcap history boost_filesystem)

ADD_EXECUTABLE(tfs_app App.cpp)
TARGET_LINK_LIBRARIES(tfs_app tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig 
	readline termcap history boost_filesystem)

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_FILE_OFFSET_BITS=64")
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_FILE_OFFSET_BITS=64")
SET(CMAKE_BUILD_TYPE Debug)

#ADD_EXECUTABLE(test_fuse fuse/src/hello.c)
#TARGET_LINK_LIBRARIES(test_fuse fuse)

#ADD_EXECUTABLE(test_hello fuse/src/hello.cpp fuse/src/testHello.cpp)
#TARGET_LINK_LIBRARIES(test_hello fuse)

#ADD_EXECUTABLE(fusetfs fuse/src/TfsHello.cpp fuse/src/main.cpp ${MODULE_CLT_ROOT}/tfs.cpp)
#TARGET_LINK_LIBRARIES(fusetfs fuse tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig)

#ADD_EXECUTABLE(tfs_shell shell/src/InputAccessor.cpp shell/src/tfsTerminal.cpp 
#	shell/src/CommandManager.cpp shell/src/FilePath.cpp shell/src/CommandExecuter.cpp 
#	shell/src/CommandLs.cpp shell/src/CommandMkdir.cpp shell/src/CommandCd.cpp 
#	shell/src/CommandGet.cpp shell/src/CommandPut.cpp shell/src/CommandRm.cpp 
#	shell/src/CommandRename.cpp)

##StartExample
#
#AUX_SOURCE_DIRECTORY(tfsshell SHELLSRC)
#ADD_EXECUTABLE(tfs_shell ${SHELLSRC})
#TARGET_LINK_LIBRARIES(tfs_shell tfs_client datatransfer tfs_ice log4cplus Ice rudeconfig 
#	readline termcap history boost_filesystem)
#
##EndExample
INCLUDE("./CMakeLists.examples.txt")

#
# INSTALL
#
INSTALL(TARGETS tfs_shell tfs_journal
    RUNTIME DESTINATION bin  
    LIBRARY DESTINATION lib  
    ARCHIVE DESTINATION lib)
