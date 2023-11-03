#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <tuple>


// Measure the length of the compressed string.
// time complexity: O(N)
// space complexity: O(1)
std::size_t count_compress(const std::string &input) {
    if (input.empty()) {
        return 0;
    }

    std::size_t compressed_length = 0;
    std::size_t count_consecutive = 0;
    for (size_t i = 0; i < input.length() - 1; ++i) {
        count_consecutive++;
        if (input[i] != input[i + 1]) {
            compressed_length += 1 + std::to_string(count_consecutive).length();
            count_consecutive = 0;
        }
    }
    compressed_length += 1 + std::to_string(count_consecutive + 1).length();

    return compressed_length;
}


// Return compressed string if the compressed string
// would be smaller than the original string, else
// return the original string.
//
// time complexity: O(N)
// space complexity: O(N)
std::string compress(const std::string &input) {
    if (input.empty()) {
        return input;
    }

    auto count_compressed = count_compress(input);
    if (count_compressed >= input.size()) {
        return input;
    }

    std::string result;
    result.reserve(std::string::size_type{count_compressed});

    int count_consecutive = 1;
    for (size_t i = 0; i < input.length() - 1; ++i) {
        if (input[i] != input[i + 1]) {
            result.push_back(input[i]);
            result.append(std::to_string(count_consecutive));
            count_consecutive = 0;
        }
        count_consecutive++;
    }
    // Add last repeated character
    result.push_back(input.back());
    result.append(std::to_string(count_consecutive));

    return result;
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
    {
        std::vector<std::tuple<std::string, int>> test_cases;
        test_cases.emplace_back("", 0);
        test_cases.emplace_back("a", 2),
        test_cases.emplace_back("aa", 2);
        test_cases.emplace_back("aaaaa", 2);
        test_cases.emplace_back("ab", 4);
        test_cases.emplace_back("aaaabbbb", 4);
        test_cases.emplace_back("ababab", 12),
        test_cases.emplace_back("aaaab", 4);
        test_cases.emplace_back("baaaa", 4);

        for (auto& [input, expected]: test_cases) {
            ASSERT_EQUAL(count_compress(input), expected);
        }
    }

    {
        std::vector<std::tuple<std::string, std::string>> test_cases;
        test_cases.emplace_back("", "");
        test_cases.emplace_back("a", "a");
        test_cases.emplace_back("aa", "aa");
        test_cases.emplace_back("aaa", "a3");
        test_cases.emplace_back("ab", "ab");
        test_cases.emplace_back("aaaabbbb", "a4b4");
        test_cases.emplace_back("aaaab", "a4b1");
        test_cases.emplace_back("aabcccccaaa", "a2b1c5a3");

        for (auto& [input, expected]: test_cases) {
            ASSERT_EQUAL(compress(input), expected);
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
