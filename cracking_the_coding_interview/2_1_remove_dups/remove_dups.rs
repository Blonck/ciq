struct ListNode {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_delete_dups() {
        let test_cases = vec![
            (vec![], vec![]),
            (vec![1], vec![1]),
            (vec![1, 2, 3], vec![1, 2, 3]),
            (vec![1, 1, 1], vec![1]),
            (vec![1, 1, 2, 2, 3, 3], vec![1, 2, 3]),
            (vec![1, 2, 3, 1, 2, 3], vec![1, 2, 3]),
        ];

        for (v1, v2) in test_cases {

            assert_eq!();
        }
    }
}
