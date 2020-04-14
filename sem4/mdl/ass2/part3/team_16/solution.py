#!/usr/bin/env python
# coding: utf-8

import numpy as np
import cvxpy as cp
import json
import os

action = ['NOOP','SHOOT','DODGE','RECHARGE']
X = 16
Y = [0.5,1,2][X % 3]
sample_state = ['enemy_health','no_of_arrows_left','stamina']
start_state = [4,3,2]

def delta(init_state : list, final_state : list) -> float:
    assert len(init_state) == 3
    assert len(final_state) == 3
    return int(init_state==final_state)

def reward(state : list, action : str) -> float:
    if action == 'NOOP':
        return 0
    return -10/Y

def prob(init_state : list, action : str, final_state : list) -> float:
    if action == 'NOOP':    
        return 0
    elif action == 'SHOOT':
        if init_state[2] - final_state[2] == 1 and (init_state[0] - final_state[0] == 1 or init_state[0] == final_state[0]) and init_state[1] - final_state[1] == 1:
            return 0.5
        return 0
    elif action == 'DODGE':
        if init_state[0] != final_state[0]:
            return 0
        if init_state[1] == 3 and final_state[1] == 3:
            prob_arrow = 1
        elif init_state[1] - final_state[1] == -1:
            prob_arrow = 0.8
        elif init_state[1] == final_state[1]:
            prob_arrow = 0.2
        else :
            return 0
        if init_state[2] == 2 and final_state[2] == 1:
            prob_stam = 0.8
        elif init_state[2] == 2 and final_state[2] == 0:
            prob_stam = 0.2
        elif init_state[2] == 1 and final_state[2] == 0:
            prob_stam = 1
        else :
            return 0
        return prob_arrow * prob_stam
    elif action == 'RECHARGE':
        if init_state[0] != final_state[0] or init_state[1] != final_state[1]:
            return 0
        elif final_state[2] - init_state[2] == 1:
            return 0.8
        elif init_state[2] == final_state[2]:
            return 0.2
        return 0

possible_states = []
for i in range(5):
    for j in range(4):
        for k in range(3):
            possible_states.append((i,j,k))

possible_act = []
for j in action:
    for i in possible_states:
        if j == 'NOOP':
            if i[0] == 0:
                possible_act.append((i,j))
        elif j == 'SHOOT':
            if i[0] != 0 and i[1] != 0 and i[2] != 0:
                possible_act.append((i,j))
        elif j == 'DODGE':
            if i[0] != 0 and i[2] != 0:
                possible_act.append((i,j))
        else:
            if i[0] != 0 and i[2] != 2:
                possible_act.append((i,j))
                
r = np.asarray([0.0 for i,_ in enumerate(possible_act)])
alpha = np.asarray([0.0 for i,_ in enumerate(possible_states)])
A = np.zeros(shape=(len(possible_states), len(possible_act)))

for i,_ in enumerate(possible_states):
    for j,_ in enumerate(possible_act):
        A[i, j] = delta(possible_states[i], possible_act[j][0]) - prob(possible_act[j][0],possible_act[j][1],possible_states[i])

for i,_ in enumerate(possible_act):
    r[i] = reward(possible_act[i][0],possible_act[i][1])

alpha[-1] = 1

def solve(A : list, alpha : str, r : str):
    doables = A.shape[1]
    x = cp.Variable(doables)
    
    objective = cp.Maximize(r @ x)
    constraints = [A @ x == alpha, x >= 0]
    prob = cp.Problem(objective, constraints)

    result = prob.solve()
    return x.value, prob.value

x,v = solve(A,alpha,r)


# Initialization of the policy dictionary
policy = {state: ('-INF', -1e100) for state in possible_states}

for i in range(len(possible_act)):
    state, act = possible_act[i]
    if policy[state][1] < x[i]:
        policy[state] = (act, x[i])

result = {
    'a': A.tolist(),
    'r': r.tolist(),
    'alpha': alpha.tolist(),
    'x': x.tolist(),
    'policy': [[list(key), act[0]] for key, act in policy.items()],
    'objective': v
}

if not os.path.exists('./outputs'):
    os.makedirs('./outputs')
with open('./outputs/output.json', 'w') as f:
    f.write(json.dumps(result))