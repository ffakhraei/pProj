#!/env/bin/python

N=36
N=30
N=1

from math import sqrt
def factors(N) :
    li = []
    if N == 1 : return [(1,1)]
    for i in xrange(1, int(sqrt(N))+1) :
        if N%i == 0 :
            li.append((i, N/i))
    return li

def solution(N) :
    minPerim=N+1
    for item in factors(N) :
        minPerim = min(minPerim, item[0]+item[1])
    return minPerim*2

print solution(N)


