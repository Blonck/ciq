use std::collections::{HashSet, LinkedList};
use std::iter::FromIterator;

// Remove all duplicates from given unsorted list.
//
// time complexity: O(N)
// space complexity: O(1)
fn delete_dups(list: &mut LinkedList<i32>) {
    let mut seen = HashSet::new();
    let mut current = list.pop_front();

    while let Some(val) = current {
        if seen.insert(val) {
            // If the value is inserted, it is not a duplicate.
            list.push_back(val);
        }
        current = list.pop_front();
    }
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

        for (input, expected) in test_cases {
            let mut list = LinkedList::from_iter(input);
            let expected_list = LinkedList::from_iter(expected);
            delete_dups(&mut list);
            assert_eq!(list, expected_list);
        }
    }
}
