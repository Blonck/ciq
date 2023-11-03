import unittest

# Return compressed string if the compressed string
# would be smaller than the original string, else
# return the original string.
#
# time complexity: O(N)
# space complexity: O(N)
def compress(input: str) -> str:
    if count_compress(input) >= len(input):
        return input

    result = []
    count_consecutive = 1
    for i in range(len(input) - 1):
        if input[i] != input[i+1]:
            result.append(input[i])
            result.append(str(count_consecutive))
            count_consecutive = 0
        count_consecutive += 1
    # Add last repeated character
    result.append(input[-1])
    result.append(str(count_consecutive))

    return ''.join(result)


# Measure the length of the compressed string.
# 
# time complexity: O(N)
# space complexity: O(1)
def count_compress(input: str) -> int:
    if not input:
        return 0

    compressed_length = 0
    count_consecutive = 0
    for c1, c2 in zip(input[:-1], input[1:]):
        count_consecutive += 1
        if c1 != c2:
            compressed_length += 1 + len(str(count_consecutive))
            count_consecutive = 0
    compressed_length += 1 + len(str(count_consecutive))

    return compressed_length

# testing the implementation


class CompressTest(unittest.TestCase):
    def test_count_compress(self):
        test_cases = [
            ("", 0),
            ("a", 2),
            ("aa", 2),
            ("aaaaa", 2),
            ("ab", 4),
            ("aaaabbbb", 4),
            ("ababab", 12),
            ("aaaab", 4),
            ("baaaa", 4),
        ]
        for input, expected in test_cases:
            self.assertEqual(count_compress(input), expected)

    def test_compress(self):
        test_cases = [
            ("", ""),
            ("a", "a"),
            ("aa", "aa"),
            ("aaa", "a3"),
            ("ab", "ab"),
            ("aaaabbbb", "a4b4"),
            ("aaaab", "a4b1"),
            ("aabcccccaaa", "a2b1c5a3"),
        ]
        for input, expected in test_cases:
            self.assertEqual(compress(input), expected)


if __name__ == "__main__":
    unittest.main()
