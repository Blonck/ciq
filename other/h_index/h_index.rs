// Calculate the h-index (https://en.wikipedia.org/wiki/H-index). Given
// a list of numbers which represent how often each paper is cited.
// The h-index is the maximum value of h such that h papers are cited
// at least h times.
// 
// time complexity: O(N)
// space complexity: O(N)
fn h_index(citations: Vec<i32>) -> i32 {
    let mut counts = vec![0; citations.len() + 1];

    // Create a list of counts
    for &citation in &citations {
        counts[std::cmp::min(citations.len(), citation as usize)] += 1;
    }

    // Reverse the counts array and create the cumsum
    let rev_cumcount: Vec<i32> = counts.iter().rev().scan(0, |acc, x| { *acc += x; Some(*acc)}).collect();

    // Determine the h-index
    rev_cumcount.iter()
        .enumerate()
        .find_map(|(i, &val)| {
            let idx = (rev_cumcount.len() - i - 1) as i32;
            (idx <= val).then(|| idx)
        })
        .unwrap_or(0)
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_h_index() {
        let test_cases = vec![
            (vec![], 0),
            (vec![1], 1),
            (vec![1, 2, 2], 2),
            (vec![1, 2, 2, 6, 4, 3], 3),
            (vec![1, 2, 3, 4, 5], 3),
            (vec![4, 4, 4, 4, 4], 4),
            (vec![100, 101, 102, 104], 4),
            (vec![104, 102, 101, 100], 4),
            (vec![100, 101, 102, 104, 1], 4),
        ];
        for (input, expected) in test_cases {
            assert_eq!(h_index(input), expected);
        }
    }
}
