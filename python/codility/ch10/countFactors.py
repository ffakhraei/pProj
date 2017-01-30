#!/bin/env/python

N=21
N=5
N=24
N=4

from math import sqrt
def solution(N) :
    if N == 1 : return 1
    numFactors = 0
    upperLimit = int(sqrt(N)) + 1
    value = sqrt(N) 
    for i in xrange(1, upperLimit) :
        if N%i == 0 :
            if i == value:
                numFactors += 1
            else:
                numFactors += 2 
    return numFactors

print solution(N)
