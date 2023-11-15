CXX = g++
CXXFLAGS=-std=c++11

all: q1 q2

q1: q1.cc
	$(CXX) $(CXXFLAGS) -o q1 q1.cc
q2: q2.cc
	$(CXX) $(CXXFLAGS) -o q2 q2.cc



run: test_q1 test_q2
test_q1: q1
	@echo running q1
	./q1

test_q2: q2
	@echo running q2
	./q2

clean:
	rm -f q1 q2