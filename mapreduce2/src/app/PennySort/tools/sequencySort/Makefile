all: PennySort PennySortO2 PennySortL
PennySort: Sort.cpp
	$(CXX) -o $@ $^
PennySortO2: Sort.cpp
	$(CXX) -O2 -o $@ $^
PennySortL: Sort.cpp
	$(CXX) -Wall -D_FILE_OFFSET_BITS=64 -o $@ $^
