// Set row[i][j] to zero and column[i][j] to zero if element matrix[i][j] is
// zero for any matrix element i, j.
//
// time complexity: O(N*N)
// space complexity: O(1)
fn zero_matrix(matrix: &mut Vec<Vec<i32>>) {
    if matrix.is_empty() || matrix[0].is_empty() {
        return;
    }

    let row_count = matrix.len();
    let col_count = matrix[0].len();

    let row_has_zero = matrix[0].iter().any(|&x| x == 0);
    let col_has_zero = matrix.iter().any(|row| row[0] == 0);

    // Mark zeros on first row and column
    for i in 1..row_count {
        for j in 1..col_count {
            if matrix[i][j] == 0 {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // Nullify rows based on marks.
    for i in 1..row_count {
        if matrix[i][0] == 0 {
            for j in 1..col_count {
                matrix[i][j] = 0;
            }
        }
    }

    // Nullify columns based on marks.
    for j in 1..col_count {
        if matrix[0][j] == 0 {
            for i in 1..row_count {
                matrix[i][j] = 0;
            }
        }
    }

    // Nullify first row.
    if row_has_zero {
        matrix[0].iter_mut().for_each(|x| *x = 0);
    }

    // Nullify first column.
    if col_has_zero {
        matrix.iter_mut().for_each(|row| row[0] = 0);
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_zero_matrx(){
        let test_cases = vec![
            (vec![vec![]], vec![vec![]]),
            (vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]], vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]]),
            (vec![vec![1, 0, 3], vec![4, 5, 6], vec![7, 8, 9]], vec![vec![0, 0, 0], vec![4, 0, 6], vec![7, 0, 9]]),
            (vec![vec![0, 2, 3], vec![4, 5, 6], vec![7, 8, 9]], vec![vec![0, 0, 0], vec![0, 5, 6], vec![0, 8, 9]]),
            (vec![vec![1, 2, 3], vec![4, 0, 6], vec![7, 8, 9]], vec![vec![1, 0, 3], vec![0, 0, 0], vec![7, 0, 9]]),
            (vec![vec![1, 2, 0], vec![4, 5, 6], vec![7, 8, 9]], vec![vec![0, 0, 0], vec![4, 5, 0], vec![7, 8, 0]]),
            (vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 0, 9]], vec![vec![1, 0, 3], vec![4, 0, 6], vec![0, 0, 0]]),
            (vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 0]], vec![vec![1, 2, 0], vec![4, 5, 0], vec![0, 0, 0]]),
        ];
        for (mut input, expected) in test_cases {
            zero_matrix(&mut input);
            assert_eq!(input, expected);
        }
    }
}
