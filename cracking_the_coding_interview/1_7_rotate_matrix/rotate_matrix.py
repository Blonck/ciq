import unittest
import numpy as np

# Rotate a NxN matrix by 90 degrees. The function returns `True`
# if the matrix can be rotated, else `False`.
#
# time complexity: O(NxN)
# space complexity: O(1)
def rotate_matrix(matrix: np.array) -> bool:
    if matrix.ndim != 2 or matrix.shape[0] != matrix.shape[1]:
        return False

    n = matrix.shape[0]
    if n == 0:
        return False

    # The matrix element are rotated layer wise, where with layer
    # the top, bottom, left and right layer is meant. 
    # Thus we need to iterate from layer 0 to N/2 to tackle every element.
    # If N is odd, the last layer consists only of a single element, the center
    # of the matrix which don't have to be rotated.
    for layer in range(n//2):
        first = layer
        last = n - 1 - layer
        # In each layer we swap the elements from the top layer with the
        # ones from the right layer. The ones from the right layer
        # with the ones from the bottom layer. The ones from the bottom layer
        # with the ones from the left layer, and finally, the ones from the left
        # layer with the ones from the top layer.
        for i in range(first, last):
            offset = i - first
            # store top element
            top = matrix[first][i]
            # left -> top
            matrix[first][i] = matrix[last-offset][first]
            # bottom -> left
            matrix[last-offset][first] = matrix[last][last-offset]
            # right -> bottom
            matrix[last][last-offset] = matrix[i][last]
            # top -> right
            matrix[i][last] = top

    return True


# test implementation


class RotateMatrixTest(unittest.TestCase):
    def test_rotate_matrix(self):
        test_cases = [
            (np.zeros((0, 0)), np.zeros((0, 0)), False),
            (np.zeros((1, 1)), np.zeros((1, 1)), True),
            (np.array([[1, 2], [3, 4]]), np.array([[3, 1], [4, 2]]), True),
            (np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]]), np.array([[7, 4, 1], [8, 5, 2], [9, 6, 3]]), True),
            (np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]),
             np.array([[13, 9, 5, 1], [14, 10, 6, 2], [15, 11, 7, 3], [16, 12, 8, 4]]), True),
            (np.array([[1, 1], [1, 1]]), np.array([[1, 1], [1, 1]]), True),
        ]
        for input, result, expected in test_cases:
            self.assertEqual(rotate_matrix(input), expected)
            np.testing.assert_array_equal(input, result)


if __name__ == "__main__":
    unittest.main()
