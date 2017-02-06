#/bin/env/python

A=[4,4,5,5,1]
B=[3,2,5,3,1]    #expected results: [5,1,8,0,1]

def fibVariant(n) :
    if n <= 2 : return n
    return fibVariant(n-2) + fibVariant(n-1)

def fibDynamicVariant(n) :
    fib = [0] * (n+2)
    fib[1] = 1
    fib[2] = 2
    for i in xrange(3, n+1) :
        fib[i] = fib[i-1] + fib[i-2]
    return fib[n]

def solution(A,B) :
    result = []
    for i in xrange(len(A)) :
        #result.append(fibVariant(A[i] % pow(2, B[i])))
        result.append(fibDynamicVariant(A[i]) % pow(2, B[i]))
    return result

print solution(A,B)
