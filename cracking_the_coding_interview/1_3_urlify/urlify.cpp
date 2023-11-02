#include <unordered_map>
#include <string>
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#include <numeric>

// Replaces all spaces from [0:true_length[ of the input
// string with '%20'. The input string is long enough to hold
// all new characters.
// 
// time complexity: O(N)
// space complexity: O(1)
void urlify(std::string& input, std::size_t true_length) {
    assert(input.size() >= true_length);

    std::size_t num_whitespaces = std::accumulate(input.begin(), input.begin()+true_length, 0,[](auto a, auto b){
        if (b == ' ') {
            return a + 1;
        } else {
          return a;
        }
    });

    // Check that the urlified string fits into the existing one.
    assert(num_whitespaces*2 + true_length <= input.size());

    // Replace all spaces by iterating over the input with two
    // pointers in reversed direction.
    int new_it = true_length - 1 + num_whitespaces * 2;
    int old_it = true_length - 1;

    while(old_it >= 0){
        if(input[old_it] == ' '){
            input[new_it--] = '0';
            input[new_it--] = '2';
            input[new_it--] = '%';
            old_it--;
        } else {
            input[new_it--] = input[old_it--];
        }
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
    std::vector<std::tuple<std::string, std::size_t, std::string>> test_cases;
    test_cases.emplace_back("Mr John Smith    ", 13, "Mr%20John%20Smith");
    test_cases.emplace_back("Mr John Smith      ", 13, "Mr%20John%20Smith  ");
    test_cases.emplace_back("Mr John Smith       ", 14, "Mr%20John%20Smith%20");
    test_cases.emplace_back("   ", 1, "%20");

    for (auto& [input, true_length, expected]: test_cases) {
        urlify(input, true_length);
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
