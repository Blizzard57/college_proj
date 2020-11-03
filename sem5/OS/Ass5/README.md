# OSNW

Roll No : 2018113003

## Assignment 5

My MLFQ algorithm was not working, and was giving errors and thus is not included in the submission. Other algorithms are described below.

## Round Robin
Ticks taken to complete: 2340
This is fast

### FCFS
Ticks taken to complete: 2501

This just finds the process with minimum time and executes it. in my testing, this is the fastest algo

## PBS
Ticks taken to complete: 2747

In this the minimum priority process is found and sent to running, after that is finished, the algo checks again if there is any process with even less amount of priority and id there is, it executes that else continues with that as the least prioirty.

This is the worst performer (MLFQ would be slower)

## MLFQ

I was not able to implement the algo, but the exploit would be to give up IO before its slice to retain the priority.