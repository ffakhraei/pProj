#/bin/env/python

A=[-8,4,5,-10,3]
#expect 3
A=[1,4,-3]
#expect 1
A=[1000000000]
#expect 2000000000

def solution(A) :
    total = float('Inf')
    n = len(A)
    if n == 1 : return abs(A[0])*2
    if n == 2 : return min(abs(A[0])*2, abs(A[1])*2, abs(A[0] + A[1]))
    for back in xrange(n) :
        front = back
        while front < n :
            if abs(A[back]+A[front]) < total :
                total = abs(A[back] + A[front])
                front += 1
            front += 1
    return total

print solution(A)
