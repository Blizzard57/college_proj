# Assignment 1
Subject : Distributed Systems
Roll No : 2018113003

## Question 1
In the first question, the code gives equal amount of numbers for all the processes to sum up and collects it back to add them up to give the complete sum.

Eg : If there are 20 digits to be summed and 5 processes, the first five digits in the sequence would go to the root process followed by the next five going to slave 1 and so on. All the processes will give the partial sum back to root process for it to sum it all up to give the complete result.

The solution should be a lot faster than serial calculation as the wors is divided equally to all process with no process having any appreciable difference in difficulty of task. Thus each process will give back the result in roughly equal amount of time, thus not making any speed up go to waste and thus making serialization worth.

## Question 2
In the second question, the code scatters the array given and spreads it equally among all the available processes. Then all the processes process quicksort serially amongst each other and then send it back to root process for it to then merge all of them together.

The solution cannot be appreciably faster than serial quicksort due to the fact that random data is being flung across processes and being sorted without any idea as to how they are situated in the complete array, thus very possibly giving rise to scenarios where all the elements need to move for the merge to take place and thus creating overhead.

There was another solution that was found on the internet and seemed that had merit was to take the array, and give half of quicksort to another process while the other half is being computed on by the same process till all processes run out. That proves a little more difficult to code and did not seem to have appreciable speed up (one reason being the maximum processors being 11).

Psuedocode :
    
    quicksort(arr):
        if(size(arr) == 1):
            return arr
        
        arr = random_array // The array to be sorted
        pivot = choose_pivot(arr)
        for all elements e in arr:
            if e < pivot:
                e belongs to left
            else:
                e belongs to right

        left = quicksort(left)
        create new process if there exists an empty one:
            right = quicksort(right)

        result = merge(left,right)
        return result

## Question 3

The third question was not coded up in time and thus did not work. The basic idea being followed was Jones-Plassmann algorithm for coding the graph. That seems like the only algorithm to provide parallelization to the graph coloring problem.