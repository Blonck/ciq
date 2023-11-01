CXX=clang++
CXXFLAGS=-Wall -std=c++20
CPP_SOURCE=unique_characters.cpp
CPP_TEST=test_unique_characters_cpp

cpp_test: $(CPP_SOURCE)
	$(CXX) $(CXXFLAGS) $(CPP_SOURCE) -o $(CPP_TEST)

run_cpp_test: cpp_test
	./$(CPP_TEST)

run_python_test: unique_characters.py
	python3 unique_characters.py

all: cpp_test

run: run_python_test run_cpp_test


