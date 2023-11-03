// Return compressed string if the compressed string
// would be smaller than the original string, else
// return the original string.
//
// time complexity: O(N)
// space complexity: O(N)
fn compress(input: &str) -> String {
    if count_compress(input) >= input.len() {
        return input.to_string();
    }

    let mut result = String::new();
    let mut count_consecutive = 1;

    let chars: Vec<char> = input.chars().collect();
    for i in 0..chars.len() - 1 {
        if chars[i] != chars[i + 1] {
            result.push(chars[i]);
            result.push_str(&count_consecutive.to_string());
            count_consecutive = 0;
        }
        count_consecutive += 1;
    }

    // Add last repeated character.
    if let Some(last) = chars.last() {
        result.push(*last);
        result.push_str(&count_consecutive.to_string());
    }

    result
}

// Measure the length of the compressed string.
//
// time complexity: O(N)
// space complexity: O(1)
fn count_compress(input: &str) -> usize {
    if input.is_empty() {
        return 0;
    }

    let mut compressed_length = 0;
    let mut count_consecutive = 0;

    let chars: Vec<char> = input.chars().collect();
    for i in 0..chars.len() - 1 {
        count_consecutive += 1;
        if chars[i] != chars[i + 1] {
            compressed_length += 1 + count_consecutive.to_string().len();
            count_consecutive = 0;
        }
    }

    // +1 for the last character
    compressed_length += 1 + count_consecutive.to_string().len() + 1;

    compressed_length
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_count_compress(){
        let test_cases = vec![
            ("", 0),
            ("a", 2),
            ("aa", 2),
            ("aaaaa", 2),
            ("ab", 4),
            ("aaaabbbb", 4),
            ("ababab", 12),
            ("aaaab", 4),
            ("baaaa", 4),
        ];
        for (input, expected) in test_cases {
            assert_eq!(count_compress(input), expected);
        }
    }

    #[test]
    fn test_compress(){
        let test_cases = vec![
            ("", ""),
            ("a", "a"),
            ("aa", "aa"),
            ("aaa", "a3"),
            ("ab", "ab"),
            ("aaaabbbb", "a4b4"),
            ("aaaab", "a4b1"),
            ("aabcccccaaa", "a2b1c5a3"),
        ];
        for (input, expected) in test_cases {
            assert_eq!(compress(input), expected);
        }
    }
}
