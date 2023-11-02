import unittest

# Replaces all spaces from [0:true_length[ of the input
# string with '%20'. The input string is long enough to hold
# all new characters.
# 
# time complexity: O(N)
# space complexity: O(N) (O[1] if a mutable string type would be used)
def urlify(input: str, true_length: int) -> str:
    num_whitespaces = input[0:true_length].count(' ')
    # Check that the urlified string fits into the existing one.
    assert(num_whitespaces*2 + true_length <= len(input))

    # Strings are immutable in python, thus convert the input to an array.
    input = [c for c in input]


    # Replace all spaces by iterating over the input with two
    # pointers in reversed direction.
    new_it = true_length - 1 + num_whitespaces * 2
    old_it = true_length - 1

    while(old_it >= 0):
        if(input[old_it] == ' '):
            input[new_it] = '0'
            input[new_it - 1] = '2'
            input[new_it - 2] = '%'
            new_it -= 3
            old_it -= 1
        else:
            input[new_it] = input[old_it]
            new_it -= 1
            old_it -= 1

    return ''.join(input)


# The pythonic way to do this would be to use the replace method of
# of the string class. Though, it would not solve the original coding task.
def urlify_pythonic(input: str, true_length: int) -> str:
    return input[0:true_length].replace(' ', '%20')


# testing the implementation


class URLifyTest(unittest.TestCase):
    def test_urlify(self):
        test_strings = [
            ("Mr John Smith    ", 13, "Mr%20John%20Smith"),
            ("Mr John Smith      ", 13, "Mr%20John%20Smith  "),
            ("Mr John Smith       ", 14, "Mr%20John%20Smith%20"),
            ("   ", 1, "%20")
        ]
        for input, true_length, expected in test_strings:
            result = urlify(input, true_length)
            self.assertEqual(result, expected)


if __name__ == "__main__":
    unittest.main()
