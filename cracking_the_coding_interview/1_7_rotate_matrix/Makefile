CXX=clang++
CXXFLAGS=-Wall -std=c++20
CUDA_COMPILER=nvcc

NAME=rotate_matrix

CPP_SOURCE=$(NAME).cpp
CPP_TEST=test_$(NAME)_test
CUDA_SOURCE=$(NAME).cu
CUDA_TEST=test_$(NAME)_cuda
PYTHON_FILE=rotate_matrix.py
RUST_FILE=rotate_matrix.rs

cpp_test: $(CPP_SOURCE)
	$(CXX) $(CXXFLAGS) $(CPP_SOURCE) -o $(CPP_TEST)

run_cpp_test: cpp_test
	./$(CPP_TEST)

run_python_test: $(PYTHON_FILE)
	python3 $(PYTHON_FILE)

run_rust_test: $(RUST_FILE)
	rustc $(RUST_FILE) --test

cuda_test: $(CUDA_SOURCE)
	$(CUDA_COMPILER) $(CUDA_SOURCE) -o $(CUDA_TEST)

run_cuda_test: cuda_test
	./$(CUDA_TEST)

all: cpp_test

run: run_python_test run_cpp_test run_rust_test run_cuda_test
