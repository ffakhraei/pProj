#!/bin/env/python

A=[]
A=[1,2]
A=[1,1] #expect 1
A=[1,1,1] 
A=[4,3,4,4,4,2]  #expect 2
A=[1,2,3,4,5]  #expect 0
A=[4,4,2,5,3,4,4,4] #expect 3

def leader(B) :
    length = len(B)
    if length == 0 :
        return None
    if length == 1 :
        return B[0]
    mod = length//2 + 1
    d = { }
    for item in B :
        if item not in d :
            d[item] = 1
        else :
            d[item] += 1
            if d[item] >= mod :
                return item
    return None

def solution(A) :
    length = len(A)
    count = 0
    if length == 0 :
        return 0
    if length == 1 :
        return 0
    if length == 2 :
        if A[0] == A[1] :
            return 1
        else :
            return 0
    for i in xrange(1,length) :
        leftLeader = leader(A[:i])
        if leftLeader != None and leftLeader == leader(A[i:length]) :
            count += 1
        else :
            continue
    return count

print solution(A)
