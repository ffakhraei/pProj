#/bin/env/python

A=[15,10,3]
B=[75,30,5]

def gcd(a,b,res=1) :
    if a == b : return res * a
    if a % 2 == 0 and b % 2 == 0 : return gcd(a//2 , b//2, res*2)
    if a % 2 == 0 and b % 2 != 0 : return gcd(a//2 , b, res)
    if a % 2 != 0 and b % 2 == 0 : return gcd(a, b//2, res)
    if a > b > 0 : return gcd(a-b, b, res)
    if b > a > 0 : return gcd(a, b-a, res)

def primeFactors(N) :
    i = 2
    S = {}
    while N > 1 :
        while N%i == 0 :
            if i not in S : 
                S[i] = 1
                N = N // i
            else : 
                #S[i] += 1
                N = N // i
        i += 1
    return S

def solution(A, B) :
    counter = 0
    for iterator in xrange(len(A)):
        if primeFactors(A[iterator]) == primeFactors(B[iterator]) :
            counter += 1
    return counter

print solution(A,B)
