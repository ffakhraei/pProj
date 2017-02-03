#!/bin/env/python

A=[1,1,1,2]
A=[1,3,2,1,5,6,3]
A=[1,1,1]
A=[1,5,3,4,3,4,1,2,3,4,6,2]

def peaks(A, n=1) :
    length = len(A)
    if length < 3 : return []
    li = []
    for i in xrange(length-2) :
        if n == 1 :
            if A[i] < A[i+1] > A[i+2] :
                li.append(i+1)
        else :
            if A[i] + n <= A[i+1] >= A[i+2] + n :
                li.append(i+1)
    return li

def solution(A) :
    length = len(A)
    if length < 3 : return 0
    pList = peaks(A)
    length = len(pList)
    if length < 3  : return length
    li=[]
    for i in xrange(length, 0, -1) :
        for j in xrange(length-1) :
            li.append(pList[j])
            for k in xrange(j+1, length) :
                if pList[k] - li[-1] >= i :
                    li.append(pList[k])
                    if len(li) == i : return i
            li=[]
    else : return 0

print solution(A)
