all: SortGen TfsSortGen SortGenL

SortGen: SortGen.cpp
	$(CXX) -o $@ $^
SortGenL: SortGen.cpp
	$(CXX) -Wall -D_FILE_OFFSET_BITS=64 -o $@ $^
TfsSortGen: TfsSortGen.cpp
	$(CXX) -o $@ $^ -ltfs_client -lIce -ltfs_ice -ldatatransfer -llog4cplus -lrudeconfig -I/home/tfs/tplatform/thirdparty/include/ -L/home/tfs/tplatform/thirdparty/lib/gcc-3.4/
