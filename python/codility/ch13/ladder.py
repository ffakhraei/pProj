#/bin/env/python

A=[4,4,5,5,1]
B=[3,2,5,3,1]    #expected results: [5,1,8,0,1]

def fib(n) :
    if n <= 2 : return n
    return fib(n-2)+fib(n-1)

def solution(A,B) :
    result = []
    for i in xrange(len(A)) :
        result.append(fib(A[i]) % pow(2, B[i]))
    return result

print solution(A,B)
