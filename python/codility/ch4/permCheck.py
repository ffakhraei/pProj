#!/bin/env/python

A=[4,1,3,2]
B=[4,1,3]
C=[2]
def solution(A):
    isPerm = 0
    maxNum = max(A)
    length = len(A)
    if len(A) != maxNum:
        return isPerm
    setA = set(A)
    if len(setA) != maxNum:
        return isPerm
    A.sort()
    for i in xrange(length):
        if A[i] != i+1:
            return isPerm
    isPerm = 1
    return isPerm
