// Checks if there exists a permutation of `input` such
// that the permutation is a palindrome.
//
// time complexity: O(N)
// space complexity: O(N)
fn is_permutation_palindrome(input: &str) -> bool {
    let mut counts = std::collections::HashMap::new();

    // For strings of even length all character counts must be even.
    // For strings of odd length all but one character counts must be even.
    // However, there is no need to handle both cases separately. If an even length
    // string is not a palindrome, at least two characters will occur a odd number.
    // Likewise, a string with odd length can't have all characters with even counts.
    for c in input.chars().filter(|c| c.is_alphanumeric()).map(|c| c.to_ascii_lowercase()) {
        let counter = counts.entry(c).or_insert(0);
        *counter += 1;
    }

    let count_odd = counts.values().filter(|&count| count % 2 == 1).count();

    count_odd <= 1
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_permutation_palindrome() {
        let test_cases = vec![
            ("", true),
            ("anna", true),
            ("Anna", true),
            ("Anna Anna", true),
            ("Tact Coa", true),
            ("[]  {}()", true),
            ("A man, a plan, a canal, Panama!", true),
            ("Not a palindrome", false),
        ];
        for (input, expected) in test_cases {
            assert_eq!(is_permutation_palindrome(input), expected);
        }
    }
}
