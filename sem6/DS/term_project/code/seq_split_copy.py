import numpy as np
import importlib
import ray
from lcg import lcg
from lfg import lfg

ray.init()

ray.remote
def seqSplitLcg(N):
    X0 = np.random.uniform(high=100)
    c = np.random.uniform(high=100)
    a = np.random.uniform(high=100)
    m = np.random.randint(low=10000,high=99999)
    
    return lcg(N,a,c,m,X0)

proc = 4
NPerProc = 10
resultIds = []
for i in range(proc):
    resultIds.append(seqSplitLcg.remote(NPerProc))

result = []
RN = ray.get(resultIds)
for i in RN:
    result.extend(i)

print(result)