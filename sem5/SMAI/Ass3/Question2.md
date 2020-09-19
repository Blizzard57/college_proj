# Assignment 3

Subject : SMAI <br>
Roll No : 2018113003

## Question 2

### Part 1

Estimation of price of house is to done. There are 9 Factors that determine price of house. Reports of 7 such houses is given. What are the issues one can face if they use Linear Regression (Closed Form) for estimation.

### Answer

Linear Regression for such a small dataset presents too many problems for it to have any sort of good estimation. It tries to estimate the prices has a linear relationship which might not be true. There is also the inherent problem that the dataset might be highly biased, which is not representative of the real data and all the values are just ouliners, which make the estimation completely off the actual value. There are many other problems but these are the major ones.

### Part 2

Will Ridge Regression help in making the estimation any better.

### Answer

Ridge Regression adds a L2 norm factor in the cost function, which depending on the value of lambda can seriosly change the rate of regression. But it doesn't help when the data itself is very and also does not help in the fact that the rgression will still try to find a linear relation between the prices. These are two cheif issues which cannot be helped by employing Ridge Regression.