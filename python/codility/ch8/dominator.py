#!/bin/env/python

A=[3,4,3,2,3,-1,3,3]

def solution(A) :
    length = len(A)
    if length == 0 :
        return -1
    if length == 1 :
        return 0
    mod = length//2 + 1
    d = { }
    for i, item in enumerate(A) :
        if item not in d :
            d[item] = 1
        else :
            d[item] += 1
            if d[item] >= mod :
                return i
    return -1

print solution(A)
