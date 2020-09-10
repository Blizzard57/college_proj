import os
import math
import collections
import itertools
import re
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns

def get_genome(filename):
    with open(filename, 'r') as f:
        ans = "".join(list(f.readlines())[1:]).replace('\n', '')
    return ans

def get_neighbor_strings(string, k):
    neighbors = set([string])
    for comb in itertools.combinations(range(len(string)), k):
        for vals in itertools.product("ATGC", repeat=k):
            copy = list(string)
            for i, val in zip(comb, vals):
                copy[i] = val
            neighbors.add(''.join(copy))
    return neighbors

def reverse_complement(genome):
    return genome.replace('A', 't').replace('T', 'a').replace('G', 'c').replace('C', 'g').replace('Y', 'r').replace('R', 'y').replace('K', 'm').replace('M', 'k').upper()[::-1]

def match(genome, d = None, k = 9):
    freq = collections.defaultdict(lambda: 0)
    for i in range(len(genome) - k):
        if d is None:
            freq[genome[i : i + k]] += 1
        else:
            for seq in get_neighbor_strings(genome[i : i + k], d):
                freq[seq] += 1
    return freq

def merge(dict1, dict2):
    for item in dict2:
        dict1[item] += dict2[item]
    return dict1

if __name__ == "__main__":
    
    m1 = merge(match(get_genome(FILES[0])), match(reverse_complement(get_genome(FILES[0]))))
    m2 = merge(match(get_genome(FILES[1])), match(reverse_complement(get_genome(FILES[1]))))
    x = merge(m1, m2)
    y = merge(match(get_genome(FILES[2])), match(reverse_complement(get_genome(FILES[2]))))

    import heapq
    print('Vibrio Cholerae:', heapq.nlargest(3, x))
    print('Salmonella enterica:', heapq.nlargest(3, y))