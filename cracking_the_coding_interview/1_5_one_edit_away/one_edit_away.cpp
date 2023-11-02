#include <unordered_map>
#include <string>
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#include <numeric>

// Check if one of the string would be edited at most one
// place, both are identical.
bool one_edit_replace(const std::string& first, const std::string& second) {
    bool found_difference = false;
    for (std::size_t i = 0; i < first.length(); ++i) {
        if (first[i] != second[i]) {
            if (found_difference) {
                return false;
            }
            found_difference = true;
        }
    }
    return true;
}

// Check if both strings are identical, if we
// could insert at one character on one of the strings.
bool one_edit_insert(const std::string& shorter, const std::string& longer) {
    std::size_t index1 = 0;
    std::size_t index2 = 0;
    while (index1 < shorter.length() && index2 < longer.length()) {
        if (shorter[index1] != longer[index2]) {
            if (index1 != index2) {
                return false;
            }
            index2++;
        } else {
            index1++;
            index2++;
        }
    }
    return true;
}

// Check if both strings are identical or only one edit away
// from each other.
//
// time complexity: O(M+N)
// space complexity: O(1)
bool one_edit_away(const std::string& first, const std::string& second) {
    if (first.length() == second.length()) {
        return one_edit_replace(first, second);
    } else if (first.length() + 1 == second.length()) {
        return one_edit_insert(first, second);
    } else if (first.length() - 1 == second.length()) {
        return one_edit_insert(second, first);
    }
    return false;
}


// test implementation


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
    std::vector<std::tuple<std::string, std::string, bool>> test_cases;
    test_cases.emplace_back("", "", true);
    test_cases.emplace_back("aa", "aa", true);
    test_cases.emplace_back("pale", "ple", true);
    test_cases.emplace_back("pales", "pale", true);
    test_cases.emplace_back("pale", "bale", true);
    test_cases.emplace_back("pale", "bae", false);
    test_cases.emplace_back("abc", "ab", true);
    test_cases.emplace_back("ab", "abc", true);
    test_cases.emplace_back("abc", "bc", true);
    test_cases.emplace_back("bc", "abc", true);
    test_cases.emplace_back("abc", "a", false);
    test_cases.emplace_back("a", "abc", false);

    for (auto& [first, second, expected]: test_cases) {
        ASSERT_EQUAL(one_edit_away(first, second), expected);
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
