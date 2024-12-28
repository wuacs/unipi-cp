// https://open.kattis.com/problems/piecesofparentheses

/*



my team solve the problem in the contest with similar idea
this is a more deep analysis

The main idea is that if some comparator can be defined so that,
if the pieces are previously sorted, always exist some optimal solution 
that can be formed following this order, 
then doing basic dp we arrive at the solution

The same notation:
pre = minimum prefix sum
len = length of bracken
sum = sum ( = +1 and ) = -1

Note that we can ignore the couples of open-closed parentheses(without change the len property) for one more clear view, this do not change any thing, then exist three types of pieces
 
1 - Open Type
    (())(( --------> is ((
    ((()( ---------> is (((
    pre >= 0

2 - Closed-Open Type
    ()))()( -------> is ))(
    ))))(())())(()(---> is )))))((
    pre < 0 && pre != sum

3 - Closed Type
    )))())---------> is )))))
    ()()()())))----> is )))
    pre < 0 && pre == sum

The Closed-Open Type has two subtypes:

2.1 - Incremental Closed-Open ( more open parentheses that closed parentheses )
      ))()())(((( -----> is )))((((
      )()(((((((( -----> is )((((((((
      pre < 0 && pre != sum && sum >= 0

2.2 - Decremental Closed-Open ( more closed parentheses that open parentheses )
      ))()())(( -----> is )))((
      ))()( -----> is ))(
      pre < 0 && pre != sum && sum < 0

Any correct sequence of pieces can be reorder in this way: 
first --------> open pieces ( in any order )
next  --------> incremental-closed-open pieces ( in decreasing order of pre ) 
next  --------> decremental-closed-open pieces ( NOT exist any correct comparator ) 
and finally --> closed pieces ( in any order )  
and the sequence remains correct

But the issue is that NOT exist any correct comparator for decremental-closed-open pieces, many teams, my team included, accepted this problem with wrong criteries for compare decremental-closed-open pieces,
for example:
- decreasing order of pre (My solution)
- decreasing order of par(pre - sum , sum)
Both criteries has WRONG SOLUTION to this case:
4
(((((
))))(
)))))((((
)

The correct idea is that if we have a good way of compare open and incremental-closed-open pieces, then we can divide the problem in two parts: 
1 - for each possible value v, what is the maximum lentgh of any sequence formed using only open and incremental-closed-open pieces, with exactly v open parentheses without couple, this problem can be solved sorting open and incremental-closed-open pieces and doing dp

2 - for each possible value v, what is the maximum lentgh of any sequence formed using only decremental-closed-open and closed pieces, with exactly v closed parentheses without couple, this problem is similar to 1 if the pieces are reverted and the parentheses are changed '('-->')' and ')'-->'('.

Now the solution for original problem would be
Max( dp[v] + dp2[v] ) for all possible value v



*/