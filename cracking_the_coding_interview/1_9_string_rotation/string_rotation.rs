// Check if s1 is a substring of s2.
fn is_substring(s1: &str, s2: &str) -> bool {
    s2.contains(s1)
}

// Check if s2 is a rotation of s1 using only a single call
// to is_substring(s1, s2)
//
// time complexity: O(N) (if is_substring is O(A+B))
// space complexity: O(N) (could be done in O(1) by concatenating the strings virtually)
fn is_string_rotation(s1: &str, s2: &str) -> bool {
    if s1.len() == s2.len() && !s1.is_empty() {
        let s1s1 = format!("{}{}", s1, s1);
        is_substring(s2, &s1s1)
    } else {
        false
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_string_rotation() {
        let test_cases = vec![
            ("", "", false),
            ("waterbottle", "erbottlewat", true),
            ("a", "a", true),
            ("a", "b", false),
            ("aaa", "a", false),
            ("ab", "ba", true),
            ("abcdefg", "bcdefga", true),
        ];

        for (s1, s2, expected) in test_cases {
            assert_eq!(is_string_rotation(s1, s2), expected);
        }
    }
}
