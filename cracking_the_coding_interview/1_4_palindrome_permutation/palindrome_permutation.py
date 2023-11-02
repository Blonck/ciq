import unittest
from collections import Counter

# Checks if there exists a permutation of `input` such
# that the permutation is a palindrome.
#
# time complexity: O(N)
# space complexity: O(N)
def is_permutation_palindrome(input: str) -> bool:
    counts = Counter(input.lower())

    # For strings of even length all character counts must be even.
    # For strings of odd length all but one character counts must be even.
    # However, there is no need to handle both cases separately. If an even length
    # string is not a palindrome, at least two characters will occur a odd number.
    # Likewise, a string with odd length can't have all characters with even counts.
    count_odd = sum((1 for c, count in counts.items() if (count % 2 == 1) and c.isalnum()))

    return count_odd <= 1



# testing the implementation


class IsPermutationPalindromeTest(unittest.TestCase):
    def test_is_permutation_palindrome(self):
        test_strings = [
            ("", True),
            ("anna", True),
            ("Anna", True),
            ("Anna Anna", True),
            ("Tact Coa", True),
            ("[]  {}()", True),
            ("A man, a plan, a canal, Panama!", True),
            ("Not a palindrome", False),
        ]
        for input, expected in test_strings:
            self.assertEqual(is_permutation_palindrome(input), expected)


if __name__ == "__main__":
    unittest.main()
