#!/bin/env/python

A=[-2,1]
A=[-2,1,-2]
A=[3,2,-6,4,0]

def solution(A) :
    length = len(A)
    if length == 0 :
        return 0
    currentSum = 0
    currentMax = A[0]
    maxVal = max(A)
    for i in xrange(length) :
        for j in xrange(i+1, length+1) :
            currentSum = sum(A[i:j+1])
            currentMax = max(currentSum, currentMax)
    return max(currentMax, maxVal)

print solution(A)
