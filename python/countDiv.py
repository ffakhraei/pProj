#/bin/env/python

A=6
B=11
K=2

def solution(A, B, K):
    #li = range(A, B+1)
    #sol = [x for x in li if x%K == 0] 
    #return len(sol)
    sol = 0
    for x in xrange(A,B+1):
        if x%K == 0:
            sol += 1
    return sol

print solution(A, B, K)


