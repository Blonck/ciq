CXX=clang++
CXXFLAGS=-Wall -std=c++20
CPP_SOURCE=is_permutation.cpp
CPP_TEST=test_is_permutation_cpp

PYTHON_FILE=is_permutation.py

RUST_FILE=is_permutation.rs

cpp_test: $(CPP_SOURCE)
	$(CXX) $(CXXFLAGS) $(CPP_SOURCE) -o $(CPP_TEST)

run_cpp_test: cpp_test
	./$(CPP_TEST)

run_python_test: $(PYTHON_FILE)
	python3 $(PYTHON_FILE)

run_rust_test: $(RUST_FILE)
	rustc $(RUST_FILE) --test

all: cpp_test

run: run_python_test run_cpp_test run_rust_test
