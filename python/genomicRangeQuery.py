#!/bin/env/python

S='CAGCCTA'
P=[2,5,0]
Q=[4,5,6]

def solution(S, P, Q):
    A, C, G, T = 1, 2, 3, 4
    result = []
    while len(P) > 0:
        lIndex = P.pop(0)
        rIndex = Q.pop(0)
        if 'A' in S[lIndex:rIndex+1]:
            result.append(1)
            continue
        if 'C' in S[lIndex:rIndex+1]:
            result.append(2)
            continue
        if 'G' in S[lIndex:rIndex+1]:
            result.append(3)
            continue
        if 'T' in S[lIndex:rIndex+1]:
            result.append(4)
            continue
    return result
print solution(S, P, Q)
