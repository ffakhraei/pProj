#!/bin/env/python

A=[1,5,2,1,4,0]

def solution(A) :
    length = len(A)
    coverage = []
    result = 0
    for i in xrange(length) :
        radius = A[i]
        li=range(i-radius, i+radius+1)
        #li.remove(i)
        coverage.append(li)
    li = [ set(x) for x in coverage]
    for i in xrange(len(li)-1) :
        for j in xrange(i+1, len(li)) :
            if len(li[i] & li[j]) > 0 :
                result += 1
                if result > 10000000 :
                    return -1 
    return result

print solution(A)
