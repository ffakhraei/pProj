#/bin/env/python

A=[1,1,0,0,0]
#expected: 2
A=[0,1,0,1,0]
#expected: 3
A=[]
#expect 1
A=[0,0,0,1,0]
#expect -1
A=[0,0,0,1,1,0,1,0,0,0,0]
#expected results: 3

#/bin/env/python

A=[0,1,0,1,0]
#expected: 3
A=[0,0,0,1,1,0,1,0,0,0,0]
#expected results: 3
A=[1,1,0,0,0]
#expected: 2

def fibDynamic(n) :
    fib = [0] * (n+2)
    fib[1] = 1
    for i in xrange(2, n+1) :
        fib[i] = fib[i-1] + fib[i-2]
    return fib[n]

def jump(A,i=0,numJumps=0) :
    length = len(A)
    if length <= 2 :
        return 1
    li = []
    while fibDynamic(i) <= length+1 :
        li.append(fibDynamic(i))
        i += 1
    li = set(li)
    if length+1 in li :
        return 1
    i = length - 1
    while i >= 0 :
        if numJumps < 0 and i > 0 : 
            i -= 1
            return 
            continue
        if A[i] :
            if i+1 in li :
                numJumps += 1
                return numJumps + solution(A[i+1:length])
        i -= 1


def solution(A) :
    length = len(A)
    if length <= 2 :
        return 1
    li = []
    i = 0
    while fibDynamic(i) <= length+1 :
        li.append(fibDynamic(i))
        i += 1
    del i
    li = set(li)
    if length+1 in li :
        return 1
    i = length - 1
    numJumps = 0
    while i >= 0 :
        if numJumps < 0 and i > 0 : 
            i -= 1
            return 
            continue
        if A[i] :
            if i+1 in li :
                numJumps += 1
                return numJumps + solution(A[i+1:length])
        i -= 1
    return -1

print solution(A)
