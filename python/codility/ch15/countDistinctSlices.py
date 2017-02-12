#/bin/env/python

A=[3,4,5,5,2]
M=6

def solution(M, A) :
    n=len(A)
    total = 0
    for back in xrange(n) :
        front = back
        while front < n and A[front] not in A[back:front] :
            total += 1
            front += 1
            if total >= 1000000000 :
                return 1000000000
    return total

print solution(M, A)
