#/bin/env/python

A=[1]
K=1
#expect 1

A=[1,2,3,4,1,1,3]
K=4
#expect 3


def solution(K, A) :
    res = 0
    n = len(A)
    i = 0
    while i < n :
        tally = A[i]
        if tally >= K :
            res += 1
        while tally < K and i < n-1 :
            #if tally + A[i+1] <= K :
            tally += A[i+1]
            i += 1 
            if tally >= K :
                res += 1
        i += 1
    return res

print solution(K, A)
