#!/bin/env/python

A=[1,3,2,1] #expect 1 [2]
A=[1,2,3,4,3,4,1,2,3,4,6,8]
A=[1,2,3,4,3,4,1,2,3,4,6,2] #expect 3 [4,6] [3,5,10]

from math import sqrt
from itertools import dropwhile
from itertools import takewhile

def peaks(A) :
    length = len(A)
    if length < 3 : return []
    li = []
    for i in xrange(length-2) :
        if A[i] < A[i+1] > A[i+2] :
            li.append(i+1)
    return li

def factors(N) :
    li = []
    for i in xrange(1, int(sqrt(N))+1) :
        if N%i == 0 :
            li.append(i)
            n=N//i
            if n not in li :
                li.append(n)
    return sorted(li)

def solution(A) :
    length = len(A)
    if length < 3 : return 0
    if length == 3 : 
        if A[0] < A[1] > A[2] : return 1
        else : return 0 
    pList = peaks(A)
    pListLength = len(pList)
    if pListLength == 0 :
        return 0
    candidates = factors(length)
    candidates.pop() #impossible to have len(A) peaks
    if len(candidates) == 0 :
        return 1
    candidates = list(dropwhile(lambda x: x > pListLength, reversed(candidates))) 
    for candidate in candidates :
        sliceLength = length // candidate
        li = pList
        for j in xrange(1, candidate+1) :
            lai = list(takewhile(lambda x: x < j*sliceLength, li))
            li = list(dropwhile(lambda x: x < j*sliceLength, li)) 
            if len(lai) == 0 :
                break
            if len(li) == 0 :
                return candidate

print solution(A)
