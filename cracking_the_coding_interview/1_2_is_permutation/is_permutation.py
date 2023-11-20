import unittest
from collections import Counter

# time complexity: O(N)
# space complexity: O(N))
def is_permutation(str1: str, str2: str) -> bool:
    return Counter(str1) == Counter(str2)



# testing the implementation


class IsPermutationTest(unittest.TestCase):
    def test_is_permutation(self):
        self.assertTrue(is_permutation("", ""))
        self.assertTrue(is_permutation("a", "a"))
        self.assertTrue(is_permutation("ab", "ab"))
        self.assertTrue(is_permutation("ab", "ba"))
        self.assertTrue(is_permutation("abcdefg12345", "gfedcba54321"))

    def test_is_not_permutation(self):
        self.assertFalse(is_permutation("", "1"))
        self.assertFalse(is_permutation("a", "ab"))
        self.assertFalse(is_permutation("abc", "abcd"))
        self.assertFalse(is_permutation("a", "aaaaaa"))
        self.assertFalse(is_permutation("ab", "abaaa"))
        self.assertFalse(is_permutation("ab", "ab "))


if __name__ == "__main__":
    unittest.main()
