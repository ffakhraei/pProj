#!/bin/env/python

X=5
A=[1,3,1,4,2,3,5,4]
def solution(X, A):
    riverArray = [0] * X
    for i in xrange(len(A)):
        if min(riverArray) != 0:
            return i
        else: 
            riverArray[A[i]-1] = A[i]
            if min(riverArray) != 0:
                return i
    if min(riverArray) == 0:
        return -1

print solution(X, A)
