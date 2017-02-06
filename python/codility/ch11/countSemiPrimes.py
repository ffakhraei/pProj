#!/bin/env/python

A=[4,6,9,10,14,15,21,22,25,26]
P=[1,4,16]
Q=[26,10,20]
N=26

#expect [10,4,0]
def primeFactors(N) :
    primesDict = {}
    for i in xrange(2, N+1) :
        while N%i == 0 :
            if i not in primesDict :
                primesDict[i] = 1
            else : primesDict[i] += 1
            N = N // i 
    return primesDict



def primes(N) :
    if N == 1 :
        return []
    result=[]
    li=[True]*(N)
    li[0] = li[1] = False
    i=2
    while i*i <= N :
        for j in xrange(i, (N-1)//i + 1) :
            li[j*i] = False
        i+=1
    del i
    #counter = 0
    for i, item in enumerate(li) :
        if li[i] :
            result.append(i)
            #counter += 1
    return result

def isSemiPrime(N) :
    if N in [1,2,3] : return False
    primesDict = {}
    i = 2 
    key = N
    while N > 1 :
        while N > 1 and N%i == 0 :
            if i not in primesDict :
                primesDict[i] = 1
            else : 
                primesDict[i] += 1
                if primesDict[i] > 2 :
                    return False
            N = N // i 
        i += 1
    if key in primesDict : return False
    length = len(primesDict)
    if length > 2 : return False
    if length == 2 :
        for key in primesDict :
            if primesDict[key] > 1 :
                return False
    return True

def solution(N,P,Q) :
    result = []
    for i in xrange(len(P)) :
        counter = 0
        #li = []
        for j in xrange(P[i], Q[i]+1) :
            if isSemiPrime(j) :
                counter += 1
                #li.append(j)
        result.append(counter)
        #result.append(li)
    return result

print solution(N,P,Q) 

