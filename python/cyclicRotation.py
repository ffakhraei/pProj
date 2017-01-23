#!/bin/env/python
B = []
if len(A) == 0:
    return A
while K>len(A):
    K %= len(A)
B[1:K] = A[len(A)-K: len(A)]
B[K:len(A)] = A[0:len(A)-K]
return B
