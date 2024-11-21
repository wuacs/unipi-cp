use assignment2::min_and_max::*;
use std::fs::*;
#[cfg(test)]
mod tests {

    use super::*;
    #[test]
    fn test_with_files() {
        const NUMBER_OF_FILES: usize = 10;
        const INPUT_PATH_PREFIX: &str = "test_files/part1/input_files/input";
        const OUTPUT_PATH_PREFIX: &str = "test_files/part1/output_files/output";
        for i in 0..=NUMBER_OF_FILES - 1 {
            let input_path: String = [
                [INPUT_PATH_PREFIX, &(i.to_string())].concat(),
                ".txt".to_string(),
            ]
            .concat();
            let output_path: String = [
                [OUTPUT_PATH_PREFIX, &(i.to_string())].concat(),
                ".txt".to_string(),
            ]
            .concat();
            let input: String = read_to_string(input_path).unwrap();
            let output: String = read_to_string(output_path).unwrap();
            let input_it: Vec<&str> = input.split(&[' ', '\n']).collect();
            let output_it: Vec<&str> = output.split(&[' ', '\n']).collect();
            let n: usize = input_it[0].parse().unwrap();
            let q: usize = input_it[1].parse().unwrap();
            let mut values: Vec<usize> = vec![0; n];
            for j in 0..n {
                values[j] = input_it[j + 2].parse().unwrap();
            }
            let mut segtree = SegmentTree::new(values, n);
            segtree.build();
            let mut output_pos = 0;
            let mut cursor_pos = n + 2;
            for j in 0..q {
                let query_type: usize = input_it[cursor_pos].parse().unwrap();
                if query_type == 0 {
                    let l: usize = input_it[cursor_pos + 1].parse().unwrap();
                    let r: usize = input_it[cursor_pos + 2].parse().unwrap();
                    let t: usize = input_it[cursor_pos + 3].parse().unwrap();
                    segtree.update(l - 1, r - 1, t);
                    cursor_pos += 4;
                } else {
                    let l: usize = input_it[cursor_pos + 1].parse().unwrap();
                    let r: usize = input_it[cursor_pos + 2].parse().unwrap();
                    let val = segtree.max(l - 1, r - 1);
                    assert_eq!(
                        val,
                        output_it[output_pos].parse().unwrap(),
                        "File: {} Test case {} failed: Query parameters (l = {}, r = {}) -> Expected {}, Got {}",
                        i,
                        j,
                        l,
                        r,
                        output_it[output_pos].parse::<u32>().unwrap(),
                        val
                    );
                    cursor_pos += 3;
                    output_pos += 1;
                }
            }
        }
    }
}
