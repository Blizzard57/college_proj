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

noSubsec = 10
aR = np.random.uniform(high=100)
aL = np.power(aR,noSubsec)

proc = 4
Lk = LCGSplit(proc,aL)

NPerProc = 10
resultIds = []
for i in range(proc):
    resultIds.append(seqSplitLcg.remote(NPerProc,Lk[i],aR))

Rk = ray.get(resultIds)

for i in range(len(Rk)):
    print(i,":",Rk[i])