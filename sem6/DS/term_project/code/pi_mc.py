# Imports
import numpy as np

# Total number of samples to be taken
N = 100000
pCiricle = 0
pt_x = 0
pt_y = 0

for i in range(N):
    # Random values of X & Y Taken
    # X,Y in [0,1]
    pt_x = np.random.uniform()
    pt_y = np.random.uniform()

    if np.square(pt_x) + np.square(pt_y) <= 1:
        # Point in circle if x^2 + y^2 < 1
        pCiricle += 1

# Area of Circle in First Quadrant
# is pi/4 (r = 1), hence pi = 4*density of 
# points in circle
pi = 4 * (pCiricle/N)
print(pi)