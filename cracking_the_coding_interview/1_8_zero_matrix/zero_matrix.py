import unittest
import numpy as np

# Set row[i][j] to zero and column[i][j] to zero if element matrix[i][j] is
# zero for any matrix element i, j.
#
# time complexity: O(N*N)
# space complexity: O(1)
def zero_matrix(matrix: np.array):
    assert(matrix.ndim == 2)

    if matrix.shape[0] == 0 or matrix.shape[1] == 0:
        return

    # Use the first row/column to mark which rows/columns
    # contains zeros.

    # Marker if first row/columns itself contains zeros.
    rowHasZero = np.any(matrix[0] == 0)
    columnHasZero = np.any(matrix[:, 0] == 0)

    # Check which elements are zero and mark them in the first row/column.
    # This can be done in a vectorized approach via `np.any(matrix == 0, axis=1),
    # but at the cost of increased space complexity.
    for index, value in np.ndenumerate(matrix[1:, 1:]):
        #print(index, value)
        if value == 0:
            #print("set to zero")

            # Need to add 1 to row/column, since iteration start at 1st index (not 0th).
            row, col = index
            matrix[row+1, 0] = 0
            matrix[0, col+1] = 0

    # Set the marked rows to zero.
    for row, value in enumerate(matrix[1:, 0]):
        if value == 0:
            # Need to add 1 to row, since iteration start at 1st index (not 0th).
            matrix[row+1, 1:] = 0

    # Set the marked columns to zero.
    for col, value in enumerate(matrix[0, 1:]):
        if value == 0:
            # Need to add 1 to column, since iteration start at 1st index (not 0th).
            matrix[1:, col+1] = 0

    if rowHasZero:
        matrix[0] = 0

    if columnHasZero:
        matrix[:, 0] = 0


class ZeroMatrixTest(unittest.TestCase):
    def test_zero_matrix(self):
        test_cases = [
            (np.zeros((0, 0)), np.zeros((0, 0))),
            (np.ones((3, 3)), np.ones((3, 3))),
            (np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]]), np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])),
            (np.array([[1, 0, 3], [4, 5, 6], [7, 8, 9]]), np.array([[0, 0, 0], [4, 0, 6], [7, 0, 9]])),
            (np.array([[0, 1, 3], [4, 5, 6], [7, 8, 9]]), np.array([[0, 0, 0], [0, 5, 6], [0, 8, 9]])),
            (np.array([[1, 2, 3], [4, 0, 6], [7, 8, 9]]), np.array([[1, 0, 3], [0, 0, 0], [7, 0, 9]])),
            (np.array([[1, 2, 0], [4, 5, 6], [7, 8, 9]]), np.array([[0, 0, 0], [4, 5, 0], [7, 8, 0]])),
            (np.array([[1, 2, 3], [4, 5, 6], [7, 0, 9]]), np.array([[1, 0, 3], [4, 0, 6], [0, 0, 0]])),
            (np.array([[1, 2, 3], [4, 5, 6], [7, 8, 0]]), np.array([[1, 2, 0], [4, 5, 0], [0, 0, 0]])),
        ]
        for input, expected in test_cases:
            zero_matrix(input)
            np.testing.assert_array_equal(input, expected)



if __name__ == "__main__":
    unittest.main()
