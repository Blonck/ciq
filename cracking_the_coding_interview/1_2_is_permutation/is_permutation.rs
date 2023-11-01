// time complexity: O(N)
// space complexity: O(N)
fn is_permutation(input1: &str, input2: &str) -> bool {
    if input1.len() != input2.len() {
        return false
    }

    let mut counts = std::collections::HashMap::new();

    for c in input1.chars() {
        let counter = counts.entry(c).or_insert(0);
        *counter += 1;
    }

    for c in input2.chars() {
        let counter = counts.entry(c).or_insert(0);
        *counter -= 1;

        if *counter < 0 {
            return false;
        }
    }

    true
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_permutation() {
        assert!(is_permutation("", ""));
        assert!(is_permutation("a", "a"));
        assert!(is_permutation("ab", "ab"));
        assert!(is_permutation("ab", "ba"));
        assert!(is_permutation("abcdefg12345", "gfedcba54321"));
    }

    #[test]
    fn test_is_not_permutation() {
        assert!(!is_permutation("", "1"));
        assert!(!is_permutation("a", "ab"));
        assert!(!is_permutation("a", "aaaaaa"));
        assert!(!is_permutation("ab", "abaaa"));
        assert!(!is_permutation("ab", "ab "));
        assert!(!is_permutation("abc", "abcd"));
    }
}
