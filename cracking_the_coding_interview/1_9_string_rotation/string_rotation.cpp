#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>

// Check if s1 is a substring of s2.
bool is_substring(const std::string& s1, const std::string& s2) {
    return s2.find(s1) != std::string::npos;
}

// Check if s2 is a rotation of s1 using only a single call
// to is_substring(s1, s2)
//
// time complexity: O(N) (if is_substring is O(A+B))
// space complexity: O(N) (could be done in O(1) by concatenating the strings virtually)
bool is_string_rotation(const std::string& s1, const std::string& s2) {
    if (s1.length() == s2.length() && !s1.empty()) {
        std::string s1s1 = s1 + s1;
        return is_substring(s2, s1s1);
    } else {
        return false;
    }
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
    test_cases.emplace_back("", "", false);
    test_cases.emplace_back("waterbottle", "erbottlewat", true);
    test_cases.emplace_back("a", "a", true);
    test_cases.emplace_back("a", "b", false);
    test_cases.emplace_back("aaa", "a", false);
    test_cases.emplace_back("ab", "ba", true);
    test_cases.emplace_back("abcdefg", "bcdefga", true);

    for (auto& [s1, s2, expected]: test_cases) {
        ASSERT_EQUAL(is_string_rotation(s1, s2), expected);
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
