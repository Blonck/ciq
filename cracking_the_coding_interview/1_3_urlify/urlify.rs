// Replaces all spaces from [0:true_length[ of the input
// string with '%20'. The input string is long enough to hold
// all new characters.
// 
// time complexity: O(N)
// space complexity: O(1)
fn urlify(input: &mut Vec<char>, true_length: usize) {
    let num_whitespaces = input[0..true_length].iter().filter(|&&c| c == ' ').count();

    let mut new_it = true_length + num_whitespaces * 2;
    let mut old_it = true_length;

    while old_it > 0 {
        old_it -= 1;
        if input[old_it] == ' ' {
            input[new_it - 1] = '0';
            input[new_it - 2] = '2';
            input[new_it - 3] = '%';
            new_it -= 3;
        } else {
            new_it -= 1;
            input[new_it] = input[old_it];
        }
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_urlify() {
        let test_cases = vec![
            ("Mr John Smith    ", 13, "Mr%20John%20Smith"),
            ("Mr John Smith      ", 13, "Mr%20John%20Smith  "),
            ("Mr John Smith       ", 14, "Mr%20John%20Smith%20"),
            ("   ", 1, "%20"),
        ];
        for (input, true_length, expected) in test_cases {
            let mut input: Vec<char> = input.chars().collect();
            urlify(&mut input, true_length);
            let expected: Vec<char> = expected.chars().collect();
            assert_eq!(input, expected);
        }
    }
}
