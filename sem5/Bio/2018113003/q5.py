import os
import math
import collections
import itertools
import re
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns

SIZE = 500

def find_content(input_file):
    with open(input_file, 'r') as f:
        genome = "".join(list(f.readlines()[1:])).replace('\n', '')

    c_a, c_t, c_g, c_c = [], [], [], []
    for i in range(0, len(genome), SIZE):
        window = genome[i:min(i + SIZE, len(genome))]
        c_a.append(window.count('A'))
        c_t.append(window.count('T'))
        c_g.append(window.count('G'))
        c_c.append(window.count('C'))

    return np.array(c_a), np.array(c_t), np.array(c_g), np.array(c_c)


if __name__ == "__main__":
    input_file = input("Enter the fasta file for the bacteria :")
    if '.fasta' != input_file[-6:]:
        input_file = input_file + '.fasta'

    no_A,no_T,no_G,no_C = find_content(input_file)

    print("The average G-C Content is : ", np.mean((no_G + no_C)/(no_A + no_C + no_G + no_T)))

