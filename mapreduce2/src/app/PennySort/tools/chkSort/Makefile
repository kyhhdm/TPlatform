all: ChkSort ChkSortL
ChkSort: ChkSort.cpp
	$(CXX) -o $@ $^
ChkSortL: ChkSort.cpp
	$(CXX) -D_FILE_OFFSET_BITS=64 -o $@ $^
