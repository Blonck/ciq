#include <unordered_map>
#include <string>
#include <cassert>
#include <iostream>

// time complexity: O(N)
// space complexity: O(N)
bool is_permutation(const std::string& input1, const std::string& input2) {
    if (input1.size() != input2.size()){
        return false;
    }

    std::unordered_map<char, int> counts;

    for(const auto c: input1) {
        counts[c]++;
    }

    for(const auto c: input2) {
        // will insert default constructed int when not existing, which is 0
        if(--counts[c] < 0) {
            return false;
        }
    }

    return true;
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


bool run_tests() {
    ASSERT(is_permutation("", ""));
    ASSERT(is_permutation("a", "a"));
    ASSERT(is_permutation("ab", "ab"));
    ASSERT(is_permutation("ab", "ba"));
    ASSERT(is_permutation("abcdefg12345", "gfedcba54321"));

    ASSERT(!is_permutation("", "1"));
    ASSERT(!is_permutation("a", "ab"));
    ASSERT(!is_permutation("a", "aaaaaa"));
    ASSERT(!is_permutation("ab", "abaaa"));
    ASSERT(!is_permutation("ab", "ab "));
    ASSERT(!is_permutation("abc", "abcd"));

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
