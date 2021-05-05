import numpy as np
import importlib
import ray
from lcg import lcg
from lfg import lfg

ray.init()

def LCGSplit(N,aL):
    X0 = np.random.uniform(high=100)
    c = np.random.uniform(high=100)
    m = np.random.randint(low=10000,high=99999)
    
    return lcg(N,aL,c,m,X0)

ray.remote
def seqSplitLcg(N,X0,aR):
    if X0 == None:
        X0 = np.random.uniform(high=100)
    c = np.random.uniform(high=100)
    m = np.random.randint(low=10000,high=99999)
    
    return lcg(N,aR,c,m,X0)

NMax = 100000
NSeq = 1000
Xf = np.array([])
for _ in range(NSeq):
    no_subsec = 4
    aL = np.random.uniform(high=100)
    aR = np.power(aL,no_subsec)

    proc = 4
    Lk = LCGSplit(proc,aL)

    NPerProc = 10
    resultIds = []
    for i in range(proc):
        resultIds.append(seqSplitLcg.remote(NPerProc,Lk[i],aR))

    Rk = ray.get(resultIds)

    val = 0
    for i in Rk:
        for j in i:
            val += j
    
    Xf = np.append(Xf,val)

print("Mean :",np.mean(Xf)/NMax,"Variance :",np.var(Xf)/(NMax**2))