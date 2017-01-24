#!/bin/env/python

A=[0,1,0,1,1]

def solution(A):
    length = len(A)
    total = 0
    while length > 0:
        if A.pop(0) == 0:
            total += A.count(1)
        length -= 1
    return total
print solution(A)
