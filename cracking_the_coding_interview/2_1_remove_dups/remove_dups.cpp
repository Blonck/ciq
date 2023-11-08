#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>
#include <list>
#include <unordered_set>

// Remove all duplicates from given unsorted list.
//
// time complexity: O(N)
// space complexity: O(1)
void delete_dups(std::list<int>& list) {
    std::unordered_set<int> seen;

    auto it = list.begin();
    while(it != list.end()) {
        if(seen.count(*it) > 0) {
            it = list.erase(it);
        } else {
            seen.insert(*it);
            ++it;
        }
    }
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

    std::vector<std::tuple<vec, vec>> test_cases;
    test_cases.emplace_back(vec{}, vec{});
    test_cases.emplace_back(vec{1}, vec{1});
    test_cases.emplace_back(vec{1, 2, 3}, vec{1, 2, 3});
    test_cases.emplace_back(vec{1, 1, 1}, vec{1});
    test_cases.emplace_back(vec{1, 1, 2, 2, 3, 3}, vec{1, 2, 3});
    test_cases.emplace_back(vec{1, 2, 3, 1, 2, 3}, vec{1, 2, 3});

    for (auto& [input, expected]: test_cases) {
        std::list<int> l1(input.begin(), input.end());
        std::list<int> l2(expected.begin(), expected.end());
        delete_dups(l1);
        ASSERT_EQUAL(l1, l2);
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
