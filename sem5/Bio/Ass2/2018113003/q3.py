import os
import math
import collections
import itertools
import re
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns

SIZE = 5*(10**4) ## 50 kb window size

def get_content(input_file):
    '''
    Finds amount of A,T,G,C content in 50 kb windows

    Return :
    --------
    The Numpy Arrays of all the content
    '''
    with open(input_file, 'r') as f:
        genome = "".join(list(f.readlines()[1:])).replace('\n', '')

    c_a, c_t, c_g, c_c = [], [], [], []
    WINDOW_SIZE = 50000
    for i in range(0, len(genome), WINDOW_SIZE):
        window = genome[i:min(i + WINDOW_SIZE, len(genome))]
        c_a.append(window.count('A'))
        c_t.append(window.count('T'))
        c_g.append(window.count('G'))
        c_c.append(window.count('C'))

    return np.array(c_a), np.array(c_t), np.array(c_g), np.array(c_c)

if __name__ == "__main__":
    input_file = input("Enter the fasta file for the bacteria :")
    if '.fasta' != input_file[-6:]:
        input_file = input_file + '.fasta'

    no_A,no_T,no_G,no_C = get_content(input_file)

    print("The average G-C Content is : ", np.mean((no_G + no_C)/(no_A + no_C + no_G + no_T)))
    print("The average G-C Skew is : ",np.mean((no_G - no_C)/(no_G + no_C)))
    print("The average A-T Skew is : ",np.mean((no_A - no_T)/(no_A + no_T)))

    print("The graphical plots can be seen on the q3.ipynb")