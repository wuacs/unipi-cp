Greedy algorithms are famous for being intuitive but not reliable.
Sometimes the solution is not even intuitive, it just works and it is easy to implement.
In this file i will provide almost-logical arguments for why a particular greedy 
algorithm works.

## Queue 

- Link problem: https://codeforces.com/contest/141/problem/C
- Link implementation: https://codeforces.com/contest/141/submission/296309275

### The intuition:
sorting by $a_i$ increasingly gives us **a** order in the queue from head to tail. This is because, intuitively, greater $a_i$'s need more elements ahead of them.

### The algorithm:
We loop through the people ordered increasingly by **a**. If the current iteration is the $ith$ iteration it means that we have already processed all people with index j such that $a_j \le a_i \land j \lt i$. 

If the current person has seen more people taller than him than people ahead of him(i.e. $ppl[i].ai > i$) then we return -1.

If we have $i$ people in the queue we need only $a[i]$ people taller than the current person to satisfy its constraint and no other. To do this we place him in position $i-a[i]$, that is the last $a[i]$ persons in the queue are considered higher than person $i$. 

### Proofs

We can now prove our algorithms correctness:

> at each iteration *i*  of the  *for* loop the array *res* contains the people up to $i$th person in the sorted array *ppl* and each person, identifiable by index *j* in the array *ppl* has exactly $a[i]$ elements ahead of it.

We prove this with induction:

say i = 1(first iteration)

then:

- if the person with lowest $a_i$ has seen more than 0 persons it means there is no head of the queue.
- Our first element is inserted in first place, as such there are exactly 0 elements ahead of it, since $a_i$ needs to be 0 from first point this concludes the base case.

say i = k - 1

then:

- If the person has $a_i$ greater than $i$ it means in any possible configuration we cannot put element $a_i$ ahead of the elements in $ppl[0..i-1]$. As such we need to put an element with value $v_j \;j \gt i\; a_j \ge a_i$ but if
  - $v_j=v_i$ then we still need $i$ elements greater and ahead of both of them, as such we pick another $k$ similarly to how we picked $j$. If we keep picking $v^*=v_j$ which would mean that element $j$ has only $i$ numbers greater than it(contradiction) or in some finite time we fall into the next case.
  - $v_j\gt v_i$ but then it is impossible that $a_j \ge a_i$ since each element taller than $v_j$ is also taller than $v_i$. Contradiction.
  - $v_j \lt v_i$ this does not add a valid element for $a_j$ so it is pointless to pick such $j$.

- For inductive hypotheses each element after index $i-ppl[i].ai$ is greater than the one before as such we have exactly $ppl[i]$ elements ahead.