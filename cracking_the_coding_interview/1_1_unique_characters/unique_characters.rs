fn is_unique_chars(s: &str) -> bool {
    let mut char_set = std::collections::HashSet::new();

    for c in s.chars() {
        if char_set.contains(&c) {
            return false;
        }
        char_set.insert(c);
    }

    true
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_unique_chars() {
        assert!(is_unique_chars(""));
        assert!(is_unique_chars("a"));
        assert!(is_unique_chars("aA"));
        assert!(is_unique_chars("1234567890abcdefghijklmnopqrstuvw"));
        assert!(is_unique_chars(" 1[](){}2"));
    }

    #[test]
    fn test_non_unique_chars() {
        assert!(!is_unique_chars("11"));
        assert!(!is_unique_chars("  "));
        assert!(!is_unique_chars("1234567890abcdefghijklmnopqrstuvw1"));
        assert!(!is_unique_chars("[["));
    }
}
