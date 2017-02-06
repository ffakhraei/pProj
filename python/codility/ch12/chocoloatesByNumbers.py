#/bin/env/python

N=10
M=4

def solution(N, M) :
    li = [True]*N
    i = 0 
    while li[i%N] :
        li[i] = False
        i += M
        i %= N
    return li.count(False)

print solution(N, M)
