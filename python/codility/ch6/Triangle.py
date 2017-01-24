#!/bin/env/python

A=[10,2,5,1,8,20]
B=[10,-2,5,1,-8,20]
C=[10,50,5,1]
D=[5,3,3]
E=[3,1,1]
F=[1]

def solution(A) :
    A.sort()
    length = len(A)
    if length < 3 :
        return 0
    for i in xrange(length-2) :
        for j in xrange(i+1,length-1) :
            for k in xrange(j+1,length) :
                if A[i] + A[j] > A[k] :
                    if A[i] + A[k] > A[j] :
                        if A[k] + A[j] > A[i] :
                            return 1
    return 0
    


print solution(A)
print solution(B)
print solution(C)
print solution(D)
print solution(E)
print solution(F)
