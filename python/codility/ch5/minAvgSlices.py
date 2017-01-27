#!/bin/env/python

A=[4,2,2,5,1,5,8]

def solution(A):
    length = len(A)
    minAvg = sum(A[:2])/2
    minIndex = 0
    for i in xrange(length):
        for j in xrange(i+1, length):
            sumSlice = sum(A[i:j+1])
            sumAvg = float(sumSlice) / (j-i+1)
            if minAvg > sumAvg:
                minAvg = sumAvg
                minIndex = i
    return minIndex

print solution(A)
