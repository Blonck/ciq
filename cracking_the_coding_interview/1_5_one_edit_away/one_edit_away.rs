
// Check if both strings are identical or only one edit away
// from each other.
//
// time complexity: O(M+N)
// space complexity: O(1)
fn one_edit_away(first: &str, second: &str) -> bool {
    // If the strings have the same length, check if they are
    // one replacement away from each other.
    if first.len() == second.len() {
        return one_edit_replace(first, second);
    // If they have a length difference of one, check if they are
    // one insert away from each other.
    } else if first.len() as i32 - 1 == second.len() as i32 {
        return one_edit_insert(second, first);
    } else if second.len() as i32 - 1 == first.len() as i32 {
        return one_edit_insert(first, second);
    } else {
        return false;
    }
}

// Check if one of the string would be edited at most one
// place, both are identical.
fn one_edit_replace(first: &str, second: &str) -> bool {
    let mut found_difference = false;
    for (c1, c2) in first.chars().zip(second.chars()) {
        if c1 != c2 {
            if found_difference {
                return false;
            }
            found_difference = true;
        }
    }
    true
}

// Check if both strings are identical, if we
// could insert at one character on one of the strings.
fn one_edit_insert(smaller: &str, larger: &str) -> bool {
    let mut it1 = smaller.chars();
    let mut it2 = larger.chars();
    let mut found_difference = false;

    while let (Some(c1), Some(c2)) = (it1.next(), it2.next()) {
        if c1 != c2 {
            if found_difference {
                return false;
            }
            found_difference = true;
            // Move back one character in the smaller string's iterator.
            it1.next_back();
        }
    }
    true
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_one_edit_away() {
        let test_cases = vec![
            ("", "", true),
            ("aa", "aa", true),
            ("pale", "ple", true),
            ("pales", "pale", true),
            ("pale", "bale", true),
            ("pale", "bae", false),
            ("abc", "ab", true),
            ("ab", "abc", true),
            ("abc", "bc", true),
            ("bc", "abc", true),
            ("abc", "a", false),
            ("a", "abc", false),
        ];

        for (first, second, expected) in test_cases {
            assert_eq!(one_edit_away(first, second), expected);
        }
    }
}
