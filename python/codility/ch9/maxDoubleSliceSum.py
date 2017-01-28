#!/bin/env/python

A=[3,2,6,-1,4,5,-1,2]

def sumDoubleSlice(A,x,y,z) :
    li = A[x+1:y]+A[y+1:z]
    mySum = sum(li)
    return mySum

def solution(A) :
    length = len(A)
    maxSum = 0
    for i in xrange(length) :
        for j in xrange(i+1, length) :
            for k in xrange(j+1,length) :
                currentSum = sumDoubleSlice(A,i,j,k)
                if maxSum < currentSum :
                    maxSum = currentSum
    return maxSum

print solution(A)
