#!/bin/env/python

N=5
A=[3,4,4,6,1,4,4]

def solution(N, A):
    counterArray = [0] * N
    length=len(A)
    for i in xrange(length):
        if A[i] >= 1 and A[i] <= N:
            counterArray[A[i]-1] += 1
        if A[i] == N+1:
            maxCount = max(counterArray)
            counterArray = [maxCount] * N
    return counterArray

print solution(N, A)
