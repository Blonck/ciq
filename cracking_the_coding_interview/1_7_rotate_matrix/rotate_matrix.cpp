#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

// Rotate a NxN matrix by 90 degrees. The function returns `True`
// if the matrix can be rotated, else `False`.
//
// Time complexity: O(N^2)
// Space complexity: O(1)
bool rotate_matrix( std::vector<std::vector<int>>& matrix )
{
    size_t n = matrix.size();

    if( n == 0 || matrix[0].size() != n ) {
        return false;
    }

    for( size_t layer = 0; layer < n / 2; ++layer ) {
        size_t first = layer;
        size_t last = n - 1 - layer;
        for( size_t i = first; i < last; ++i ) {
            size_t offset = i - first;
            // store top element
            int top = matrix[first][i];
            // left -> top
            matrix[first][i] = matrix[last - offset][first];
            // bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset];
            // right -> bottom
            matrix[last][last - offset] = matrix[i][last];
            // top -> right
            matrix[i][last] = top;
        }
    }

    return true;
}

// Test implementation

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

#define ASSERT( expression )                                                                       \
    if( !( expression ) ) {                                                                        \
        std::cerr << "Assertion failed: " << #expression << "\nFile: " << __FILE__ << "\n"         \
                  << "\nLine: " << __LINE__ << "\n";                                               \
        return false;                                                                              \
    }

#define ASSERT_EQUAL( a, b )                                                                       \
    if( ( a ) != ( b ) ) {                                                                         \
        std::cerr << "Assertion failed: " << #a << " == " << #b << "\n"                            \
                  << #a << " = " << ( a ) << ", " << #b << " = " << ( b )                          \
                  << "\nFile: " << __FILE__ << "\n"                                                \
                  << "\nLine: " << __LINE__ << "\n";                                               \
        return false;                                                                              \
    }

bool run_tests()
{
    std::vector<std::tuple<matrix, matrix, bool>> test_cases;
    test_cases.emplace_back( matrix{ {} }, matrix{ {} }, false );
    test_cases.emplace_back( matrix{ { 1, 2 }, { 3, 4 } }, matrix{ { 3, 1 }, { 4, 2 } }, true );
    test_cases.emplace_back( matrix{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } },
                             matrix{ { 7, 4, 1 }, { 8, 5, 2 }, { 9, 6, 3 } }, true );
    test_cases.emplace_back(
        matrix{ { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } },
        matrix{ { 13, 9, 5, 1 }, { 14, 10, 6, 2 }, { 15, 11, 7, 3 }, { 16, 12, 8, 4 } }, true );
    test_cases.emplace_back( matrix{ { 1, 1 }, { 1, 1 } }, matrix{ { 1, 1 }, { 1, 1 } }, true );

    for( auto& [input, result, expected] : test_cases ) {
        ASSERT_EQUAL( rotate_matrix( input ), expected );
        ASSERT_EQUAL( input, result );
    }

    return true;
}

int main()
{
    if( run_tests() ) {
        std::cout << "C++ test succeeded\n";
        return 0;
    } else {
        std::cout << "Failure in C++ tests\n";
        return 1;
    }
}
