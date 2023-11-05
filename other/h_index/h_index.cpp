#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

//// a list of numbers which represent how often each paper is cited.
// The h-index is the maximum value of h such that h papers are cited
// at least h times.
// 
// time complexity: O(N)
// space complexity: O(N)
int h_index(const std::vector<int>& citations) {
    std::vector<int> counts(citations.size() + 1, 0);

    // Create a list of counts
    for (int citation : citations) {
        counts[std::min(citations.size(), static_cast<size_t>(citation))]++;
    }

    // Reverse the counts array and create the cumsum
    std::vector<int> rev_cum_count(counts.size());
    int cumsum = 0;
    std::transform(counts.rbegin(), counts.rend(), rev_cum_count.begin(),
                   [&cumsum](int count) { cumsum += count; return cumsum;});

    // Determine the h-index
    for (size_t i = 0; i < rev_cum_count.size(); ++i) {
        int idx = static_cast<int>(rev_cum_count.size() - i - 1);
        if (idx <= rev_cum_count[i]) {
            return idx;
        }
    }
    return 0;
}


// test implementation


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
    using vec = std::vector<int>;
    std::vector<std::tuple<std::vector<int>, int>> test_cases;
    test_cases.emplace_back(vec{}, 0);
    test_cases.emplace_back(vec{1}, 1);
    test_cases.emplace_back(vec{1, 2, 2}, 2);
    test_cases.emplace_back(vec{1, 2, 2, 6, 4, 3}, 3);
    test_cases.emplace_back(vec{4, 4, 4, 4, 4}, 4);
    test_cases.emplace_back(vec{100, 101, 102, 104}, 4);
    test_cases.emplace_back(vec{104, 102, 101, 100}, 4);

    for( auto& [input, expected] : test_cases ) {
        ASSERT_EQUAL(h_index(input), expected);
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
