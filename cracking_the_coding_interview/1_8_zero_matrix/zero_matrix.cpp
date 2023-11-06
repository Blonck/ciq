#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <tuple>

// Set row[i][j] to zero and column[i][j] to zero if element matrix[i][j] is
// zero for any matrix element i, j.
//
// time complexity: O(N*N)
// space complexity: O(1)
void zero_matrix(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return;
    }

    const int row_count = matrix.size();
    const int col_count = matrix[0].size();

    bool row_has_zero = false;
    for (int j = 0; j < col_count; ++j) {
        if (matrix[0][j] == 0) {
            row_has_zero = true;
            break;
        }
    }

    bool col_has_zero = false;
    for (int i = 0; i < row_count; ++i) {
        if (matrix[i][0] == 0) {
            col_has_zero = true;
            break;
        }
    }

    // Mark zeros on first row and column.
    for (int i = 1; i < row_count; ++i) {
        for (int j = 1; j < col_count; ++j) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // Nullify rows based on marks.
    for (int i = 1; i < row_count; ++i) {
        if (matrix[i][0] == 0) {
            std::fill(matrix[i].begin() + 1, matrix[i].end(), 0);
        }
    }

    // Nullify columns based on marks.
    for (int j = 1; j < col_count; ++j) {
        if (matrix[0][j] == 0) {
            for (int i = 1; i < row_count; ++i) {
                matrix[i][j] = 0;
            }
        }
    }

    // Nullify first row.
    if (row_has_zero) {
        std::fill(matrix[0].begin(), matrix[0].end(), 0);
    }

    // Nullify first column.
    if (col_has_zero) {
        for (auto& row : matrix) {
            row[0] = 0;
        }
    }
}


// test implementation

using matrix = std::vector<std::vector<int>>;

// Overload the operator<< to print a std::vector<std::vector<int>>
std::ostream& operator<<( std::ostream& os, const std::vector<std::vector<int>>& matrix )
{
    for( const auto& row : matrix ) {
        for( const auto& elem : row ) {
            os << elem << ' ';
        }
        os << '\n';
    }
    return os;
}


#define ASSERT(expression)                               \
    if(!(expression))                                    \
    {                                                    \
        std::cerr << "Assertion failed: " << #expression \
                  << "\nFile: " << __FILE__ << "\n"      \
                  << "\nLine: " << __LINE__ << "\n";     \
        return false;                                    \
    }

#define ASSERT_EQUAL(a, b)                                \
    if((a) != (b))                                        \
    {                                                     \
        std::cerr << "Assertion failed: " << #a << " == " \
                  << #b << "\n" << #a << " = " << (a)     \
                  << ", " << #b << " = " << (b)           \
                  << "\nFile: " << __FILE__ << "\n"       \
                  << "\nLine: " << __LINE__ << "\n";      \
        return false;                                     \
    }


bool run_tests() {
    std::vector<std::tuple<matrix, matrix>> test_cases;
    test_cases.emplace_back(matrix{}, matrix{});
    test_cases.emplace_back(matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    test_cases.emplace_back(matrix{{1, 0, 3}, {4, 5, 6}, {7, 8, 9}}, matrix{{0, 0, 0}, {4, 0, 6}, {7, 0, 9}});
    test_cases.emplace_back(matrix{{0, 2, 3}, {4, 5, 6}, {7, 8, 9}}, matrix{{0, 0, 0}, {0, 5, 6}, {0, 8, 9}});
    test_cases.emplace_back(matrix{{1, 2, 3}, {4, 0, 6}, {7, 8, 9}}, matrix{{1, 0, 3}, {0, 0, 0}, {7, 0, 9}});
    test_cases.emplace_back(matrix{{1, 2, 0}, {4, 5, 6}, {7, 8, 9}}, matrix{{0, 0, 0}, {4, 5, 0}, {7, 8, 0}});
    test_cases.emplace_back(matrix{{1, 2, 3}, {4, 5, 6}, {7, 0, 9}}, matrix{{1, 0, 3}, {4, 0, 6}, {0, 0, 0}});
    test_cases.emplace_back(matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}, matrix{{1, 2, 0}, {4, 5, 0}, {0, 0, 0}});

    for (auto& [input, expected]: test_cases) {
        zero_matrix(input);
        ASSERT_EQUAL(input, expected);
    }

    return true;
}


int main() {
    if(run_tests()) {
        std::cout << "C++ test succeeded\n";
        return 0;
    } else {
        std::cout << "Failure in C++ tests\n";
        return 1;
    }
}
