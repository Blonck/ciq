// Rotate a NxN matrix by 90 degrees. The function is
// adopted to the rust style and returns a `Result` instead of a boolean.
//
// Time complexity: O(N^2)
// Space complexity: O(1)
fn rotate_matrix(matrix: &mut Vec<Vec<i32>>) -> Result<(), &str> {
    let n = matrix.len();

    // Check if matrix is non-empty and square
    if n == 0 || matrix.iter().any(|row| row.len() != n) {
        return Err("Matrix must be non-empty and square");
    }

    for layer in 0..n / 2 {
        let first = layer;
        let last = n - 1 - layer;
        for i in first..last {
            let offset = i - first;
            let top = matrix[first][i];
            // left -> top
            matrix[first][i] = matrix[last - offset][first];
            // bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset];
            // right -> bottom
            matrix[last][last - offset] = matrix[i][last];
            // top -> right
            matrix[i][last] = top;
        }
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_rotate_matrix() {
        let mut matrix2 = vec![vec![1]];
        let mut matrix3 = vec![vec![1, 2], vec![3, 4]];
        let mut matrix4 = vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]];
        let mut matrix5 = vec![
            vec![1, 2, 3, 4],
            vec![5, 6, 7, 8],
            vec![9, 10, 11, 12],
            vec![13, 14, 15, 16],
        ];

        assert!(rotate_matrix(&mut vec![vec![]]).is_err());
        assert!(rotate_matrix(&mut matrix2).is_ok());
        assert!(rotate_matrix(&mut matrix3).is_ok());
        assert!(rotate_matrix(&mut matrix4).is_ok());
        assert!(rotate_matrix(&mut matrix5).is_ok());

        assert_eq!(matrix2, vec![vec![1]]);
        assert_eq!(matrix3, vec![vec![3, 1], vec![4, 2]]);
        assert_eq!(matrix4, vec![vec![7, 4, 1], vec![8, 5, 2], vec![9, 6, 3]]);
        assert_eq!(
            matrix5,
            vec![
                vec![13, 9, 5, 1],
                vec![14, 10, 6, 2],
                vec![15, 11, 7, 3],
                vec![16, 12, 8, 4]
            ]
        );
    }
}
