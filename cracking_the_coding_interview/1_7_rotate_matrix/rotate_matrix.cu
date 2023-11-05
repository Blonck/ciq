#include <cuda_runtime.h>
#include <stdio.h>

#include <iostream>
#include <tuple>
#include <vector>

__device__ __forceinline__ int idx(int x, int y, int width) {
  return y * width + x;
}

__global__ void rotate_matrix_dev(int* matrix, int n) {
  int x = blockIdx.x * blockDim.x + threadIdx.x;
  int y = blockIdx.y * blockDim.y + threadIdx.y;

  if (x < (n + 1) / 2 && y < (n + 1) / 2) {
    // save top left
    int tmp = matrix[idx(x, y, n)];
    // replace top left with bottom left
    matrix[idx(x, y, n)] = matrix[idx(y, n - 1 - x, n)];
    // replace bottom left with bottom right
    matrix[idx(y, n - 1 - x, n)] = matrix[idx(n - 1 - x, n - 1 - y, n)];
    // replace bottom right with top right
    matrix[idx(n - 1 - x, n - 1 - y, n)] = matrix[idx(n - 1 - y, x, n)];
    // replace top right with temporary (top left)
    matrix[idx(n - 1 - y, x, n)] = tmp;
  }
}

void rotate_matrix(int* matrix, int n) {
  int* d_matrix;

  cudaMalloc(&d_matrix, n * n * sizeof(int));
  cudaMemcpy(d_matrix, matrix, n * n * sizeof(int), cudaMemcpyHostToDevice);

  dim3 threadsPerBlock(1, 1);
  dim3 blocksPerGrid((n + threadsPerBlock.x - 1) / threadsPerBlock.x,
                     (n + threadsPerBlock.y - 1) / threadsPerBlock.y);

  rotate_matrix_dev<<<blocksPerGrid, threadsPerBlock>>>(d_matrix, n);

  cudaMemcpy(matrix, d_matrix, n * n * sizeof(int), cudaMemcpyDeviceToHost);

  cudaFree(d_matrix);
}

// test implementation

using vec = std::vector<int>;

// Overload the operator<< to print a std::vector<std::vector<int>>
std::ostream& operator<<(std::ostream& os, const vec& matrix) {
  std::size_t n = static_cast<std::size_t>(std::sqrt(matrix.size()));

  for (std::size_t row = 0; row < n; ++row) {
    for (std::size_t col = 0; col < n; ++col) {
      os << matrix[row * n + col] << ' ';
    }
    os << '\n';
  }
  return os;
}

#define ASSERT(expression)                                                     \
  if (!(expression)) {                                                         \
    std::cerr << "Assertion failed: " << #expression << "\nFile: " << __FILE__ \
              << "\n"                                                          \
              << "\nLine: " << __LINE__ << "\n";                               \
    return false;                                                              \
  }

#define ASSERT_EQUAL(a, b)                                          \
  if ((a) != (b)) {                                                 \
    std::cerr << "Assertion failed: " << #a << " == " << #b << "\n" \
              << #a << " = " << (a) << ", " << #b << " = " << (b)   \
              << "\nFile: " << __FILE__ << "\n"                     \
              << "\nLine: " << __LINE__ << "\n";                    \
    return false;                                                   \
  }

bool run_tests() {
  std::vector<std::tuple<vec, vec>> test_cases;
  test_cases.emplace_back(vec{}, vec{});
  test_cases.emplace_back(vec{1, 2, 3, 4}, vec{3, 1, 4, 2});
  test_cases.emplace_back(vec{1, 2, 3, 4, 5, 6, 7, 8, 9},
                          vec{7, 4, 1, 8, 5, 2, 9, 6, 3});
  test_cases.emplace_back(
      vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
      vec{13, 9, 5, 1, 14, 10, 6, 2, 15, 11, 7, 3, 16, 12, 8, 4});
  test_cases.emplace_back(vec{1, 1, 1, 1}, vec{1, 1, 1, 1});

  for (auto& [input, expected] : test_cases) {
    int n = static_cast<int>(std::sqrt(input.size()));
    rotate_matrix(input.data(), n);
    ASSERT_EQUAL(input, expected);
  }

  return true;
}

int main() {
  if (run_tests()) {
    std::cout << "CUDA test succeeded\n";
    return 0;
  } else {
    std::cout << "Failure in CUDA tests\n";
    return 1;
  }
}
