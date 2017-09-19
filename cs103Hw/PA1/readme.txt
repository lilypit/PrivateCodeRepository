CSCI 103 Programming Assignment 1, Hailstone

Name: Jacob Pitts

Email Address: jacobpit@usc.edu

NOTE: You can delete the questions, we only need your responses.
================================ Questions ==================================

1. Which kind of a loop did you use for the first program? Why?

: Since we did not know many times the program would have to loop, I used 
a while loop. In doing so, I was able to ensure that the program would run
as many times as it would take for the input to reach 1.

2a. Once you've completed the second program, run hailstats on the following
inputs, and record your results in the table below:


 input range  | minimum length | achieved by | maximum length | achieved by
-----------------------------------------------------------------------------
    50 100     |      6          |       64      |        118        |  97
   100 200     |      7          |       128      |       124         |  171
   200 400     |      8          |       256      |       143         |  327

2b. What pattern do you think there is in the values achieving minimum length?
Can you explain why it holds?

: As the input range doubles, the minimum length increases 
by one. This pattern likely is explainable by the fact that the program 
divides by two before increasing the length. Since doubling the 
input value would require the program to run an extra time, 
this statement holds. 

3a. Let X be the smallest integer whose length is greater than 150.
By running your hailstats program several times on carefully chosen inputs,
determine what is the value of X.

X is 703 

3b. Explain, briefly, the way in which you used your hailstats program
(i.e., which inputs you gave it) to find this answer.

: First chose relatively high inputs (1 - 1000) and narrowed it down. After 
running the hailstats program with a range of 1-700, 
it yielded a maximum value of 144,meaning I was getting close. 
Continuing to run the program, this time with a range of 700-705, 
the maximum length turned out to be 170, with the prior numbers 
being 82. Since the only yielded numbers before 170 were 82, 
the first number that yielded 170 would be X, which ultimately 
ended up being 703. 
================================ Remarks ====================================