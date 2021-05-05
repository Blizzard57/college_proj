import numpy as np
import importlib
import ray
from lcg import lcg
from lfg import lfg

ray.init()

@ray.remote
def seqSplitLfg(N):
    seed = str(np.random.randint(low=10000000,high=99999999))
    p = 3
    q = 7
    m = np.random.randint(low=10000,high=99999)
    N = 10

    return lfg(N,seed,p,q,m)

proc = 4
NPerProc = 10
resultIds = []
for i in range(proc):
    resultIds.append(seqSplitLfg.remote(NPerProc))

result = []
RN = ray.get(resultIds)
for i in RN:
    result.extend(i)

print(result)