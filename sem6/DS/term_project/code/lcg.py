import numpy as np

def lcg(N,a,c,m,X0):
    X = [X0]
    for i in range(N):
        X.append((a*X[-1] + c)%m)

    return X

if __name__ == "__main__":
    X0 = np.random.uniform(high=100)
    c = np.random.uniform(high=100)
    a = np.random.uniform(high=100)
    m = np.random.randint(low=10000,high=99999)
    N = 10

    print(lcg(N,a,c,m,X0))
