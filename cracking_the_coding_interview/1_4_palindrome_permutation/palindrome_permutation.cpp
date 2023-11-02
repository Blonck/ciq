#include <unordered_map>
#include <string>
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#include <numeric>

// Checks if there exists a permutation of `input` such
// that the permutation is a palindrome.
//
// time complexity: O(N)
// space complexity: O(N)
bool is_permutation_palindrome(const std::string& input) {
    std::unordered_map<char, int> counts;

    // For strings of even length all character counts must be even.
    // For strings of odd length all but one character counts must be even.
    // However, there is no need to handle both cases separately. If an even length
    // string is not a palindrome, at least two characters will occur a odd number.
    // Likewise, a string with odd length can't have all characters with even counts.
    for (char c : input) {
        if (isalnum(c)) {
            char lower_c = std::tolower(c);
            counts[lower_c]++;
        }
    }

    const int count_odd = std::accumulate(counts.begin(), counts.end(), 0, [](auto a, auto b){
        return a + (b.second % 2);
    });

    return count_odd <= 1;
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
    std::vector<std::tuple<std::string, bool>> test_cases;
    test_cases.emplace_back("", true);
    test_cases.emplace_back("anna", true);
    test_cases.emplace_back("Anna", true);
    test_cases.emplace_back("Anna Anna", true);
    test_cases.emplace_back("Tact Coa", true);
    test_cases.emplace_back("[]  {}()", true);
    test_cases.emplace_back("A man, a plan, a canal, Panama!", true);
    test_cases.emplace_back("Not a palindrome", false);

    for (auto& [input, expected]: test_cases) {
        ASSERT_EQUAL(is_permutation_palindrome(input), expected);
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
