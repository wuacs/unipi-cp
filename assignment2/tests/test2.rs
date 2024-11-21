use assignment2::is_there::*;
use std::fs::*;
#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_with_files() {
        const INPUT_PATH_PREFIX: &str = "test_files/part2/input_files/input";
        const OUTPUT_PATH_PREFIX: &str = "test_files/part2/output_files/output";
        for i in 0..=7 {
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
            let mut segments: Vec<(usize, usize)> = vec![];
            for j in 0..n {
                segments.push((
                    input_it[2 * j + 2].parse().unwrap(),
                    input_it[2 * j + 3].parse().unwrap(),
                ));
            }
            let mut segtree = SegmentTreeSet::new(n);
            segtree.build(segments);
            for j in 0..q {
                let l: usize = input_it[2 * n + 3 * j + 2].parse().unwrap();
                let r: usize = input_it[2 * n + 3 * j + 3].parse().unwrap();
                let k: usize = input_it[2 * n + 3 * j + 4].parse().unwrap();

                let mut val: u32 = 0;

                if segtree.is_there(l, r, k) {
                    val = 1;
                }

                assert_eq!(
                    val,
                    output_it[j].parse().unwrap(),
                    "Test case {} failed: Query parameters (l = {}, r = {}, k = {}) -> Expected {}, Got {}",
                    j,
                    l,
                    r,
                    k,
                    output_it[j].parse::<u32>().unwrap(),
                    val
                );
            }
        }
    }
}
