/// Segment Tree Utility functions
mod stu {
    pub fn left(index: usize) -> usize {
        2 * index + 1
    }

    pub fn right(index: usize) -> usize {
        2 * index + 2
    }

    pub fn mid(start: usize, end: usize) -> usize {
        (start + end) >> 1
    }
}

pub mod min_and_max {
    use super::stu;
    use std::cmp::max;
    use std::cmp::min;
    /// Struct based on segment trees which answers `Max` and `Update` 
    /// queries in logarithmic time
    pub struct SegmentTree {
        values: Vec<usize>,
        tree: Vec<usize>,
        lazy: Vec<usize>,
        size: usize,
    }

    impl SegmentTree {
        pub fn new(values: Vec<usize>, size: usize) -> Self {
            SegmentTree {
                values,
                tree: vec![0; 4 * size],
                lazy: vec![usize::MAX; 4 * size],
                size,
            }
        }

        pub fn build(&mut self) {
            self.build_helper(0, self.size - 1, 0);
        }

        fn build_helper(&mut self, start: usize, end: usize, node: usize) {
            if start == end {
                self.tree[node] = self.values[start];
                return;
            }
            let mid: usize = stu::mid(start, end);
            self.build_helper(start, mid, stu::left(node));
            self.build_helper(mid + 1, end, stu::right(node));
            self.tree[node] = max(self.tree[stu::left(node)], self.tree[stu::right(node)]);
        }

        fn update_helper(
            &mut self,
            l: usize,
            r: usize,
            start: usize,
            end: usize,
            node: usize,
            t: usize,
        ) {
            self.propagate(node, start, end);
            if start > r || end < l {
                return;
            }
            if start >= l && end <= r {
                self.lazy[node] = min(self.lazy[node], t);
                self.propagate(node, start, end);
                return;
            }
            let mid = (start + end) >> 1;
            if start == end {
                return;
            }
            self.update_helper(l, r, start, mid, stu::left(node), t);
            self.update_helper(l, r, mid + 1, end, stu::right(node), t);
            self.tree[node] = max(self.tree[stu::left(node)], self.tree[stu::right(node)]);
        }

        pub fn update(&mut self, l: usize, r: usize, t: usize) {
            self.update_helper(l, r, 0, self.size - 1, 0, t);
        }

        fn propagate(&mut self, index: usize, l: usize, r: usize) {
            if self.lazy[index] != usize::MAX {
                if l < r {
                    self.lazy[stu::left(index)] = min(self.lazy[index], self.lazy[2 * index + 1]);
                    self.lazy[stu::right(index)] = min(self.lazy[index], self.lazy[2 * index + 2]);
                }
                self.tree[index] = min(self.tree[index], self.lazy[index]);
                self.lazy[index] = usize::MAX;
            }
        }

        pub fn max(&mut self, l: usize, r: usize) -> usize {
            self.max_helper(l, r, 0, self.size - 1, 0)
        }

        fn max_helper(
            &mut self,
            l: usize,
            r: usize,
            start: usize,
            end: usize,
            node: usize,
        ) -> usize {
            self.propagate(node, start, end);
            if start > r || end < l {
                return 0;
            }
            if start >= l && end <= r {
                return self.tree[node];
            }
            let mid = stu::mid(start, end);
            let left = self.max_helper(l, r, start, mid, stu::left(node));
            let right = self.max_helper(l, r, mid + 1, end, stu::right(node));
            max(left, right)
        }
    }
}

pub mod is_there {
    use crate::stu::{left, right};

    use super::stu;
    use std::collections::BTreeSet;
    /// Helper struct which enables `stabbing queries`
    struct SegmentTreeStab {
        tree: Vec<usize>, // Holds counts of intervals
    }
    impl SegmentTreeStab {
        fn new(size: usize) -> Self {
            SegmentTreeStab {
                tree: vec![0; 4 * size],
            }
        }
        /// The update recursive procedure which adds the inclusive interval
        /// \[l, r] to the nodes which are fully contained in it, effectively
        /// updating the cardinality of the intervals canonical set.
        fn update(&mut self, l: usize, r: usize, start: usize, end: usize, node: usize) {
            if r < start || l > end {
                return;
            }
            if l <= start && end <= r {
                self.tree[node] += 1;
                return;
            }
            let mid = stu::mid(start, end);
            self.update(l, r, start, mid, stu::left(node));
            self.update(l, r, mid + 1, end, stu::right(node));
        }

        /// Function which performs a relaxed version of a stabbing query
        /// where it is returned the number of segments containing a given point `p`
        fn query(&self, p: usize, start: usize, end: usize, node: usize) -> usize {
            if p < start || p > end {
                return 0;
            }
            if start == end {
                return self.tree[node];
            }
            let mid = stu::mid(start, end);
            let left = self.query(p, start, mid, stu::left(node));
            let right = self.query(p, mid + 1, end, stu::right(node));
            left + right + self.tree[node]
        }
    }
    /// Struct based on segment trees which answers `isThere` queries in 
    /// logarithmic time
    pub struct SegmentTreeSet {
        tree: Vec<BTreeSet<usize>>,
        size: usize,
    }
    impl SegmentTreeSet {
        pub fn new(size: usize) -> Self {
            SegmentTreeSet {
                tree: vec![BTreeSet::new(); 4 * size],
                size,
            }
        }
        /// Separate build function that initializes the segment tree with the
        /// vector of intervals `intervals`.
        pub fn build(&mut self, intervals: Vec<(usize, usize)>) {
            let mut stab_tree = SegmentTreeStab::new(self.size);

            for (l, r) in &intervals {
                stab_tree.update(*l, *r, 0, self.size - 1, 0);
            }

            for i in 0..self.size {
                let result = stab_tree.query(i, 0, self.size - 1, 0);
                self.update(i, result, 0, self.size - 1, 0);
            }
        }
        /// A function which returns whether there is a point `t` (`i` <= `t` <= `j`)
        /// such that exactly `k` segments contain `t`.
        pub fn is_there(&mut self, i: usize, j: usize, k: usize) -> bool {
            self.query(i, j, k, 0, self.size - 1, 0)
        }
        /// Adds to every interval containing point `k` the information
        /// that there are `val` segments which contain `k`.
        fn update(&mut self, k: usize, val: usize, start: usize, end: usize, node: usize) {
            if k < start || k > end {
                return;
            }
            if k >= start && k <= end {
                self.tree[node].insert(val);
            }
            if start == end {
                return;
            }
            let mid = stu::mid(start, end);
            self.update(k, val, start, mid, left(node));
            self.update(k, val, mid + 1, end, right(node));
        }
        /// Recursive helper function for the `is_there` function 
        fn query(
            &self,
            l: usize,
            r: usize,
            k: usize,
            start: usize,
            end: usize,
            node: usize,
        ) -> bool {
            if r < start || l > end {
                return false;
            }
            if l <= start && end <= r {
                return self.tree[node].contains(&k);
            }
            let mid = stu::mid(start, end);
            let left = self.query(l, r, k, start, mid, left(node));
            let right = self.query(l, r, k, mid + 1, end, right(node));
            left || right
        }
    }
}
