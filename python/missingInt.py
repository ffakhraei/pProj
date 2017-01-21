#!/bin/env/python

A=[1,3,6,4,1,2]
B=[-100, -50, 0, 1, 2, 4]
C=[0,0,0]
D=[-1]
E=[0]
F=[1]
def solution(A):
    A.sort()
    minMissing = 1
    for i in xrange(len(A)):
        if A[i] <= 0:
            continue
        if A[i] > minMissing:
            return minMissing
        elif A[i] == minMissing:
            minMissing += 1
    return minMissing
print solution(A)
print solution(B)
print solution(C)
print solution(D)
print solution(E)
print solution(F)
