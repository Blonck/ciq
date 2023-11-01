import unittest

# time complexity: O(N)
# space complexity: O(N)
def is_unique_chars_01(input: str) -> bool:
    seen = set()

    for c in input:
        if c in seen:
            return False
        seen.add(c)

    return True


# same as `is_unique_chars_01`, "more" pythonic
# but no early return
def is_unique_chars_02(input: str) -> bool:
    return len(input) == len(set(input))


# time complexity: O(N log(N))
# space complexity: O(1)
# but modifies input
def is_unique_chars_03(input: str) -> bool:
    input = sorted(input)
    for a, b in zip(input[:-1], input[1:]):
        if a == b:
            return False
    return True


# testing the implementation

# minimal wrapper to specify multiple functions under test
def parameterized_test(test_data):
    def decorator(test_func):
        def wrapper(self):
            for i, fut in enumerate(test_data):
                with self.subTest(i=i, fut=fut):
                    test_func(self, fut)
        return wrapper
    return decorator


class UniqueCharsTest(unittest.TestCase):
    @parameterized_test([is_unique_chars_01, is_unique_chars_02, is_unique_chars_03])
    def test_unique_chars(self, fut):
        self.assertTrue(fut(""))

        self.assertTrue(fut("a"))

        self.assertTrue(fut("aA"))

        self.assertTrue(fut("1234567890abcdefghijklmnopqrstuvw"))

        self.assertTrue(fut(" 1[](){}2"))

    @parameterized_test([is_unique_chars_01, is_unique_chars_02, is_unique_chars_03])
    def test_non_unqiue_chars(self, fut):
        self.assertFalse(fut("11"))

        self.assertFalse(fut("  "))

        self.assertFalse(fut("1234567890abcdefghijklmnopqrstuvw1"))

        self.assertFalse(fut("[["))


if __name__ == "__main__":
    unittest.main()
