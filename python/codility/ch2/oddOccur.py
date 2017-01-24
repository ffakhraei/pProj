#!/bin/env/python
A=[1,3,5,3,1]
#for item in A:
#    if A.count(item)%2 != 0:
#        print item
def solution(A):
    A.sort()
    counter=1
    for i in xrange(len(A)-1):
        if A[i+1] == A[i]:
            counter += 1
        else:
            if counter%2 != 0:
                return A[i]
            if i == len(A)-1:
                return A[i]
            counter=1
            continue
    return A[len(A)-1]
print solution(A)
    
