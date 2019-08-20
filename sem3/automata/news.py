import json

def powerset(fullset):
    listrep = list(fullset)
    n = len(listrep)
    return [[listrep[k] for k in range(n) if i&1<<k] for i in range(2**n)]

out = {}
val = json.load(open('nfa.json'))
subset=list(range(val['states']))
pq = list(powerset(subset))
start=[]
final=[]
t=[]
for i in pq:
    if val['start'] in i:
        start.append(list(i))    
    for j in val['letters']:
        nex_st = []
        for k in val['t_func']:
            if k[0] in i and j == k[1]:
                nex_st.append(k[2])
        t.append([list(i),j,list(nex_st)])
    for j in val['final']:
        if j in i:
            final.append(list(i))

out['states'] = 2**val['states']
out['letters'] = val['letters']
out['t_func'] = t
out['start'] = start
out['final'] = final
with open('out.json', 'w') as outfile:
    json.dump(out, outfile,indent=4)
