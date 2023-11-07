import unittest

# Check if s1 is a substring of s2.
def is_substring(s1, s2):
    return s1 in s2

# Check if s2 is a rotation of s1 using only a single call
# to is_substring(s1, s2)
#
# time complexity: O(N) (if is_substring is O(A+B))
# space complexity: O(N) (could be done in O(1) via itertools.chain() and
#                         and a custom is_substring implementation)
def is_string_rotation(s1: str, s2: str) -> bool:
    if len(s1) == len(s2) and s1:
        s1s1 = s1 + s1
        return s2 in s1s1
    return False


# test implementation


class IsStringRotationTest(unittest.TestCase):
    def test_is_string_rotation(self):
        test_cases = [
            ("", "", False),
            ("waterbottle", "erbottlewat", True),
            ("a", "a", True),
            ("a", "b", False),
            ("aaa", "a", False),
            ("ab", "ba", True),
            ("abcdefg", "bcdefga", True),
        ]
        for s1, s2, expected in test_cases:
            self.assertEqual(is_string_rotation(s1, s2), expected)



if __name__ == "__main__":
    unittest.main()
