#/bin/env/python

A=[10,2,5,1,8,12] 

def isTriangle(a,b,c) :
    if a+b > c and a+c > b and b+c > a :
        return True
    return False

def solution(A) :
    n = len(A)
    total = 0
    for a in xrange(n) :
        for b in xrange (a+1, n) :
            for c in xrange(b+1, n) :
                if isTriangle(A[a],A[b],A[c]) :
                    total += 1
    return total

print solution(A)
