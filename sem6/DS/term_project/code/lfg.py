import numpy as np

def lfg(N,seed,p,q,m):
    seed = [int(i) for i in list(seed)]
    if len(seed) <= max(p,q):
        raise ValueError("Bigger seed required")

    X = []

    for i in range(N):
        val = (seed[p]*seed[q])%m
        seed.append(val)
        X.append(val)
        p = p + 1
        q = q + 1

    return X

if __name__ == "__main__":
    seed = str(np.random.randint(low=10000000,high=99999999))
    p = 3
    q = 7
    m = np.random.randint(low=10000,high=99999)
    N = 10

    print(lfg(N,seed,p,q,m))
