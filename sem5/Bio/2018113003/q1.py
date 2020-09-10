import os
import math
import collections
import itertools
import re
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns

def flat_to_fasta(input):
    '''
    The function which does a line by line conversion of .fasta file to .gb file

    Parameters :
    ------------
    definition : str

    accession : str

    sequence : str
    '''
    ## Variables
    definition = None 
    accession = None
    sequence = None

    ## Combining defintions and sequences
    for strings in input.readlines():
        if strings[:10] == 'DEFINITION':
            definition = " ".join(strings.split(" ")[1:]).strip()
        elif strings[:9] == "ACCESSION":
            accession = " ".join(strings.split(" ")[1:]).strip()
        elif strings[:6] == "ORIGIN":
            sequence = ""
        elif strings[:1] == " " and sequence is not None:
            break
        elif sequence is not None:
            string += strings.strip().upper()
    return '>' + definition + ' ' + accession + '\n' + (sequence if sequence is not None else '')

def fasta_to_flat(input):
    '''
    The function which does a line by line conversion of .gb file to .fasta file

    Parameters :
    ------------
    definition : str

    sequence : str
    '''

    ## Variables
    definition, sequence = None, ""
    
    ## Seperating definitons and sequences
    for _, strings in enumerate(input.readlines()):
        if strings[:1] == '>':
            definition = strings[1:].strip()
        else:
            sequence += strings.strip()


    header = "{:12s}{}\n{:12s}{}\n{:12s}{}\n{:12s}{}\n{:12s}{}\n{:12s}{}\n{:12s}{}\n{:12s}{}\n{:21s}{}\n{:s}\n".format(
        "LOCUS", definition.split(" ")[0],
        "DEFINITION", definition,
        "ACCESSION",definition.split(" ")[0].split(".")[0],
        "VERSION", definition.split(" ")[0],
        "KEYWORDS", ".",
        "SOURCE", ".",
        "  ORGANISM", ".",
        "", ".",
        "FEATURES", "Location/Qualifiers",
        "ORIGIN",
    )

    l = len(sequence)
    for i in range(0,l - 60,60):
        for j in range(i,min(i+60,l),10):
            genome = '\n'.join(['{:>9} {} {} {} {} {} {}'.format(i + 1, *[sequence[j : min(j + 10, l)]])])

    return header + genome + '\n'

if __name__ == "__main__":

    ## Input and Output files
    ## If file extension not provided, add it itself
    choice = input("Conversion Flat to Fasta(F) or Fasta to Flat(A) (Enter F for Flat -> Fasta, A for Fasta -> Flat :")
    if(choice is 'F'):
        input_file = input("The input file name : ")
        if '.gb' != input_file[-2:]:
            input_file = input_file + '.gb'

        output = input("The output file name : ")
        if '.fasta' != output[-6:]:
            output = output + '.fasta'

        with open(output, 'w') as f:
            f.write(flat_to_fasta(open(input_file, 'r')))
        exit(0)

    ## Input and Output files
    ## If file extension not provided, add it itself
    input_file = input("The input file name : ")
    if '.fasta' != input_file[-6:]:
        input_file = input_file + '.fasta'

    output = input("The output file name : ")
    if '.gb' != output[-2:]:
        output = output + '.gb'

    with open(output, 'w') as f:
        f.write(fasta_to_flat(open( input_file, 'r')))
    
    exit(0)