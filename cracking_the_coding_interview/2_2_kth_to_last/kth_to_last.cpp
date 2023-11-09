#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>
#include <list>

// Finds the kth to the last element of the provided singly linked list.
//
// time complexity: O(N)
// space complexity: O(1)
std::list<int>::const_iterator kth_to_last(const std::list<int>& list, size_t k) {
    auto it1 = list.begin();
    auto it2 = list.begin();

    // Forward it1 k times.
    for (size_t i = 0; i < k; ++i) {
        if (it1 == list.end()) {
            return it1;
        }
        ++it1;
    }
    if (it1 == list.end()) {
        return it1;
    }

    // Now it1 is k positions in advance of it2. When it1 is exhausted
    // it2 is at the kth to the last position. However we must take care
    // to advance it2 not if it1 is already exhausted (at list.end()).
    while(++it1 != list.end()) {
        ++it2;
    }

    return it2;
}

// test implementation

std::ostream& operator<<(std::ostream& os, const std::list<int>& list) {
    os << "[";
    for (auto e: list) {
        os << e << ",";
    }
    os << "]";

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::list<int>::const_iterator it) {
    os << *it;
    return os;
}

// Find the ith element of the provided list.
std::list<int>::const_iterator get_ith_node(const std::list<int>& l, int i) {
    if (i < 0) {
        return l.end();
    }

    auto it = l.begin();

    // Iterate through the list until the ith element or end of the list
    for (size_t index = 0; index < i && it != l.end(); ++index) {
        ++it;
    }

    // If i is larger than the list size, it will return list.end()
    return it;
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
    using vec = std::vector<int>;

    std::vector<std::tuple<vec, int>> test_cases;
    test_cases.emplace_back(vec{}, 2);
    test_cases.emplace_back(vec{1}, 0);
    test_cases.emplace_back(vec{1}, 1);
    test_cases.emplace_back(vec{1, 1}, 1);
    test_cases.emplace_back(vec{1, 2}, 0);
    test_cases.emplace_back(vec{1, 2}, 1);
    test_cases.emplace_back(vec{1, 2}, 2);
    test_cases.emplace_back(vec{1, 2, 3, 4, 1, 2, 3, 4}, 0);
    test_cases.emplace_back(vec{1, 2, 3, 4, 1, 2, 3, 4}, 1);
    test_cases.emplace_back(vec{1, 2, 3, 4, 1, 2, 3, 4}, 5);
    test_cases.emplace_back(vec{1, 2, 3, 4, 1, 2, 3, 4}, 100);

    for (auto& [input, k]: test_cases) {
        std::list<int> l(input.begin(), input.end());
        auto kth = kth_to_last(l, k);
        auto expected = get_ith_node(l, static_cast<int>(input.size()) - k - 1);
        if(expected == l.end()) {
            ASSERT_EQUAL(kth, l.end());
        } else {
            ASSERT_EQUAL(*kth, *expected);
        }
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
