import itertools
import unittest

# Calculate the h-index (https://en.wikipedia.org/wiki/H-index). Given
# a list of numbers which represent how often each paper is cited.
# The h-index is the maximum value of h such that h papers are cited
# at least h times.
# 
# time complexity: O(N)
# space complexity: O(N)
def h_index(citations: list[int]) -> int:
    counts = [0] * (len(citations) + 1)

    # Create a list of counts, the 0th index counts the number 
    # of papers with 0 citations, the 1st index counts the number
    # of papers with 1 citations, and so on.
    for citation in citations:
        counts[min(len(citations), citation)] += 1

    # Reverse the counts array and create the cumsum.
    rev_cum_count = list(itertools.accumulate(reversed(counts)))

    # The first index in the reversed cumsum array where the value
    # is smaller or equal then the `reversed` index, represent the
    # h-index.
    for i, val in enumerate(rev_cum_count):
        idx = len(rev_cum_count) - i - 1
        if idx <= val:
            return idx
    return 0

# test implementation


class HIndexTest(unittest.TestCase):

    def test_h_index(self):
        test_cases = [
            ([], 0),
            ([1], 1),
            ([1, 2, 2], 2),
            ([1, 2, 2, 6, 4, 3], 3),
            ([1, 2, 3, 4, 5], 3),
            ([4, 4, 4, 4, 4], 4),
            ([100, 101, 102, 104], 4),
            (list(reversed([100, 101, 102, 104])), 4),
            ([100, 101, 102, 104, 1], 4),
        ]
        for input, expected in test_cases:
            self.assertEqual(h_index(input), expected)


if __name__ == "__main__":
    unittest.main()
