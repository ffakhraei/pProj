#!/bin/env/python

A=[23171,21011,21123,21366,21013,21367]

def solution(A) :
    length = len(A)
    if length == 0 :
        return 0
    maxProfit=0
    maxVal = max(A)
    minVal = min(A)
    if A.index(minVal) < A.index(maxVal) :
        maxProfit = maxVal - minVal 
        return maxProfit
    for i in xrange(length) :
        for j in xrange(i+1, length) :
            maxProfit = max(maxProfit, A[j] - A[i])
    return maxProfit

print solution(A)
