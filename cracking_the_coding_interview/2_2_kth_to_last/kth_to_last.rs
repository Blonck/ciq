use std::collections::LinkedList;

// Finds the kth to the last element of the provided singly linked list.
//
// time complexity: O(N)
// space complexity: O(1)
fn kth_to_last(list: &LinkedList<i32>, k: usize) -> Option<&i32> {
    let mut it1 = list.iter();
    let mut it2 = list.iter();

    // Advance it1 by k steps.
    for _ in 0..k {
        if it1.next().is_none() {
            return None;
        }
    }

    // Now it1 is k positions ahead of it2. When it1 reaches the end,
    // it2 will be at the kth to the last element.
    while it1.next().is_some() {
        it2.next();
    }

    it2.next()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_kth_to_last() {
        let test_cases = vec![
            (vec![], 2),
            (vec![1], 0),
            (vec![1], 1),
            (vec![1, 1], 1),
            (vec![1, 2], 0),
            (vec![1, 2], 1),
            (vec![1, 2], 2),
            (vec![1, 2, 3, 4, 1, 2, 3, 4], 0),
            (vec![1, 2, 3, 4, 1, 2, 3, 4], 1),
            (vec![1, 2, 3, 4, 1, 2, 3, 4], 5),
            (vec![1, 2, 3, 4, 1, 2, 3, 4], 100),
        ];

        for (input, k) in test_cases {
            let list: LinkedList<_> = input.into_iter().collect();
            let result = kth_to_last(&list, k);
            let expected = list.iter().rev().nth(k);

            assert_eq!(result, expected);
        }
    }
}
