CXX=clang++ 
CXXFLAGS=-Wall -pedantic -Werror -std=c++11 -pipe

all: debug 

debug: CXXFLAGS += -g -ggdb -O0 -DDEBUG
debug: compile

opt: CXXFLAGS+= -march=native -O3 -DNDEBUG
opt: compile

compile:
	$(CXX) $(CXXFLAGS) -o prog.exe *.cpp