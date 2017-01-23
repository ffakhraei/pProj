#!/bin/env/python

A=[3,1,2,4,3]
B=[1,0]
C=[1,2,3]
D=[1,2,3,4,5,6,7,8,9,10]
def solution(A):
    sumTotal = sum(A)
    for i in xrange(1,len(A)):
        #Ahigh = A[i:len(A)]
        #Alow = A[:i]
        #sumHigh = sum(Ahigh)
        sumLow = sum(A[:i])
        sumHigh = sumTotal - sumLow
        diff = abs(sumLow - sumHigh)
        if i == 1:
            minDiff = diff
        else:
            minDiff = min(diff, minDiff)
    return minDiff 
print solution(A)
print solution(B)
print solution(C)
print solution(D)

    


