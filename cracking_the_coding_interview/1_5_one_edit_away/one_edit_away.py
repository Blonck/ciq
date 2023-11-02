import unittest


# Check if both strings are identical or only one edit away
# from each other.
#
# time complexity: O(M+N)
# space complexity: O(1)
def one_edit_away(first: str, second: str) -> bool:

    # If the strings have the same length, check if they are
    # one replacement away from each other.
    if len(first) == len(second):
        return one_edit_replace(first, second)
    # If they have a length difference of one, check if they are
    # one insert away from each other.
    elif len(first) - 1 == len(second):
        return one_edit_insert(second, first)
    elif len(second) - 1 == len(first):
        return one_edit_insert(first, second)
    else:
        return False

# Check if one of the string would be edited at most one
# place, both are identical.
def one_edit_replace(first: str, second: str) -> bool:
    # Just go through both strings, return `False` as
    # soon as we find a second difference.
    found_difference = False

    for c1, c2 in zip(first, second):
        if c1 != c2:
            if found_difference:
                return False
            found_difference = True;

    return True


# Check if both strings are identical, if we
# could insert at one character on one of the strings.
def one_edit_insert(smaller: str, larger: str) -> bool:
    it1 = 0
    it2 = 0
    while it1 < len(smaller) and it2 < len(larger):
        c1 = smaller[it1]
        c2 = larger[it2]
        # If we found the first difference, advance only the iterator
        # of the larger string.
        if c1 != c2:
            # If the iterators are different, this is already the second difference.
            if it1 != it2:
                return False
            it2 += 1
        else:
            it1 += 1
            it2 += 1

    return True

# testing the implementation


class OneEditAwayTest(unittest.TestCase):
    def test_one_edit_away(self):
        test_cases = [
            ("", "", True),
            ("aa", "aa", True),
            ("pale", "ple", True),
            ("pales", "pale", True),
            ("pale", "bale", True),
            ("pale", "bae", False),
            ("abc", "ab", True),
            ("ab", "abc", True),
            ("abc", "bc", True),
            ("bc", "abc", True),
            ("abc", "a", False),
            ("a", "abc", False),
        ]
        for first, second, expected in test_cases:
            self.assertEqual(one_edit_away(first, second), expected)


if __name__ == "__main__":
    unittest.main()
