import os
import math
import collections
import itertools
import re
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns

def rem_quotes(str):
    if str[0] == '"':
        return str[1:-1]
    return str

def feat_table(input_file):
    '''
    The main function which does the parsing

    output : dict

    running : bool

    running_label : str

    last_el : str
    '''
    output = {}

    with open(input_file, 'r') as f:
        running = False
        label = None

        for line in f.readlines():
            if (not running and line[:9] == 'FEATURES') or (running and line[0] != ' '):
                running = not running
                label = None
            
            elif running and line.strip().startswith('/'):
                output[label][line.strip().split('=')[0][1:]] = rem_quotes(line.strip().split('=')[1])
            
            elif running:
                label = line.strip().split(' ')[0]
                output[label] = {}

    return output

if __name__ == "__main__":
    input_file = input('The Input File name : ')

    if '.gb' != input_file[-2:]:
        input_file = input_file + '.gb'

    print(feat_table(input_file))