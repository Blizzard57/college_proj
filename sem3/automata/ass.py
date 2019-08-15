## Importing JSON API
import json
## Importing the library for listing the powerset
from itertools import chain, combinations

def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))

## Opening and accessing data from json file
data = json.load(open('nfa.json'))
## No of states required for DFA
s = 2**data['states']

## The n states of the NFA
ls=[]
for i in range(data['states']):
    ls.append(i)
pq = list(powerset(ls))

## The Delta Function
t = []
for i in pq:
    for j in data['letters']:
        nex_st = set()
        for k in data['t_func']:
            if k[0] in i and j == k[1]:
                nex_st.update(k[2])
        t.append([list(i),j,list(nex_st)])

## The Start state        
st=[]
for i in pq:
    if data['start'] in i:
        st.append(list(i))

## The Final state
fin=[]
for i in pq:
    for j in data['final']:
        if j in i:
            fin.append(list(i))

## Making a dictionary to save the output as a JSON
out = {}
out['states'] = []
out['states'].append(s)
out['letters'] = data['letters']
out['t_func'] = t
out['start'] = st
out['final'] = fin
with open('out.json', 'w') as outfile:
    json.dump(out, outfile,indent=4)