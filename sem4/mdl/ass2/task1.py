import numpy as np
import os

team_no = 16  # team number
# Hence, step_cost = -10
step_cost = -10
bellman = 10**-3
discount = 0.99

# (health,arrows,stamina)
state_v = np.zeros( shape=(5, 4, 3) )

states = []
for h in range(5):
    for a in range(4):
        for s in range(3):
            states.append((h,a,s))


# setting up constant lists
act = ["SHOOT", "DODGE", "RECHARGE"]
stamina = [0, 50, 100]
health = [0, 25, 50, 75, 100]
arrow = [0, 1, 2, 3]


def task_setup(no: int) -> str:
    global step_cost, discount, bellman
    if no == 1:
        task_file = "./outputs/task_1_trace.txt"

    elif no == 2:
        task_file = "./outputs/task_2_part_1_trace.txt"
        step_cost = -2.5

    elif no == 3:
        discount = 0.1
        step_cost = -2.5
        task_file = "./outputs/task_2_part_2_trace.txt"

    elif no == 4:
        step_cost = -2.5
        discount = 0.1
        bellman = 1e-10
        task_file = "./outputs/task_2_part_3_trace.txt"

    # New file for dumping output
    with open( task_file, mode='w' ) as f:
        pass

    return task_file


def Print(itr: int, action_index: np.ndarray, task_file: str, debug: int = 1) -> None:
    assert action_index.size == state_v.size
    if debug == 1:
        print( "iteration={}\n".format( itr ) )
        for h, a, s in states:
            temp = -1
            if h != 0:
                temp = act[action_index[h][a][s]]
            print( "({0},{1},{2}):{3}=[{4:.3f}]\n".format( h, a, s, temp, state_v[h][a][s] ) )
        print( "\n\n" )

    else:
        with open( task_file, mode='a' ) as f:
            f.write( "iteration={}\n".format( itr ) )
            for h, a, s in states:
                temp = -1
                if h != 0:
                    temp = act[action_index[h][a][s]]

                f.write(
                    "({0},{1},{2}):{3}=[{4:.3f}]\n".format( h, a, s, temp, state_v[h][a][s] ) )
            f.write( "\n\n" )


def Utility(s: int, a: int, h: int, action: int) -> float:
    # Shoot
    # if h-1==0, give reward
    if action == 0 and s > 0 and a > 0:  
        return (0.5 * state_v[h, a - 1, s - 1] + 0.5 * state_v[h - 1, a - 1, s - 1]) if (h - 1 != 0) else (
                0.5 * state_v[h, a - 1, s - 1] + 0.5 * 10)  
    # Dodge
    elif action == 1 and s > 0:  
        temp = 0.8 * state_v[h, min( a + 1, 3 ), 0] + 0.2 * state_v[h, a, 0]
        if s == 2:
            temp = 0.8 * 0.8 * state_v[h, min( a + 1, 3 ), 1] + 0.2 * 0.8 * state_v[h, a, 1] + 0.2 * temp
        return temp

    elif action == 2:
        return 0.2 * state_v[h, a, s] + 0.8 * state_v[h, a, min( 2, s + 1 )]

    # penalty so that this is not considered in the max
    return -100000.0  


def VI_algorithm(task_no: int) -> None:
    global state_v
    task_file = task_setup( task_no )

    # 4th dimension ==> actions
    Temp_table = np.zeros( shape=(5, 4, 3, 3) )  

    for itr in range(1, 1000):
        for h, a, s in states:
            for action in range(3):
                # skip terminal states
                if h == 0: 
                    continue
                
                # Task 2-2
                elif task_no == 2 and action == 0:  
                    Temp_table[h, a, s, action] = -0.25 + discount * Utility( s, a, h, action )
                
                # the usual cases to handle
                else:  
                    Temp_table[h, a, s, action] = step_cost + discount * Utility( s, a, h, action )

        #Max Utility
        max_table = np.max( Temp_table, axis=3 )
        assert max_table.size == state_v.size

        action_index = np.argmax( Temp_table,axis=3 ) 
        val = np.max( np.abs( max_table - state_v ) )
        
        state_v = max_table
        Print( itr, action_index, debug=0, task_file=task_file )

        if val < bellman:  # end condition for algorithm
            break

if __name__ == "__main__":
    os.mkdir( './outputs' )
    for task in range(1,5):
        VI_algorithm(task)