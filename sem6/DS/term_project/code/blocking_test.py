import numpy as np
import importlib
import ray
from lcg import lcg
from lfg import lfg

ray.init()

@ray.remote
def seqSplitLcg(N):
    X0 = np.random.uniform(high=100)
    c = np.random.uniform(high=100)
    a = np.random.uniform(high=100)
    m = np.random.randint(low=10000,high=99999)
    
    return lcg(N,a,c,m,X0)

NMax = 100000
NProc = 1000
Xf = np.array([])
for _ in range(NProc):
    proc = 4
    NPerProc = 10
    resultIds = []
    for i in range(proc):
        resultIds.append(seqSplitLcg.remote(NPerProc))

    result = []
    RN = ray.get(resultIds)
    for i in RN:
        result.append(i)
    
    val = 0
    for i in result:
        for j in i:
            val += j 

    Xf = np.append(Xf,val)

print("Mean :",np.mean(Xf)/NMax,"Variance :",np.var(Xf)/(NMax**2))