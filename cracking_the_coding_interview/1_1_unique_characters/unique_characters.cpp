#include <cstddef>
#include <unordered_set>
#include <vector>
#include <string>
#include <cassert>
#include <functional>
#include <iostream>
#include <algorithm>

// time complexity: O(N)
// space complexity: O(N)
bool is_unique_chars_01(const std::string& input) {
    std::unordered_set<char> seen;

    for(const auto& c: input) {
        if (seen.contains(c)) {
            return false;
        }
        seen.insert(c);
    }

    return true;
}

// time complexity: O(N log(N))
// space complexity: O(1)
// modifies input
bool is_unique_chars_02(std::string& input) {
    if(input.empty()){
        return true;
    }

    std::sort(input.begin(), input.end());

    for(std::size_t i=0; i < input.size()-1; ++i) {
        if (input[i] == input[i+1]) {
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
    }


bool run_tests() {

    std::vector<std::function<bool(const std::string&)>> futs;
    futs.push_back([](const std::string& input) {return is_unique_chars_01(input);});

    for(auto& fut: futs) {
        ASSERT(fut(""));
        ASSERT(fut("a"));
        ASSERT(fut("aA"));
        ASSERT(fut("1234567890abcdefghijklmnopqrstuvw"));
        ASSERT(fut(" 1[](){}2"));

        ASSERT(!fut("11"));
        ASSERT(!fut("  "));
        ASSERT(!fut("1234567890abcdefghijklmnopqrstuvw1"));
        ASSERT(!fut("[["));
    }

    std::vector<std::function<bool(std::string&)>> futs2;
    futs2.push_back([](std::string& input) {return is_unique_chars_02(input);});

    for(auto& fut: futs2) {
        std::string input = "";
        ASSERT(fut(input));
        input = "a";
        ASSERT(fut(input));
        input = "aA";
        ASSERT(fut(input));
        input = "1234567890abcdefghijklmnopqrstuvw";
        ASSERT(fut(input));
        input = " 1[](){}2";
        ASSERT(fut(input));

        input = "11";
        ASSERT(!fut(input));
        input = "  ";
        ASSERT(!fut(input));
        input = "1234567890abcdefghijklmnopqrstuvw1";
        ASSERT(!fut(input));
        input = "[[";
        ASSERT(!fut(input));
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
