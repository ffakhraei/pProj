#!/bin/env/python
A=[2,3,1,5]
B=[]
C=[1,2]
D=[1,3]
E=[2,3]

def solution(A):
    A.sort()
    if len(A) == 0:
        return 1
    elif len(A) == 1:
        if A[0] == 1:
            return 2
        else:
            return A[0] - 1
    elif len(A) == 2:
        if A[1] - A[0] == 1:
            if A[0] != 1:
                return 1
            else:
                return A[1]+1
    for i in xrange(len(A)-1):
        if A[i+1]-A[i] != 1:
            return A[i]+1
    if A[0] == 1:
        return A[len(A)-1] + 1
    else:
        return A[0] - 1
print solution(A)
print solution(B)
print solution(C)
print solution(D)
print solution(E)
