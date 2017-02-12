#/bin/env/python

A=[0,0,0,1,0]
#expect -1
A=[0,1,0,1,0]
#expected: 3
A=[]
#expect 1
A=[1,1,0,0,0]
#expected: 2
A=[0,0,0,1,1,0,1,0,0,0,0]
#expected results: 3

def fibDynamic(n) :
    fib = [0] * (n+2)
    fib[1] = 1
    for i in xrange(2, n+1) :
        fib[i] = fib[i-1] + fib[i-2]
    return fib[n]

global crossed 
global jumpIndexList
crossed = False
jumpIndexList = []

def solution(A) :
    global crossed
    length = len(A)
    if length <= 2 :
        return 1
    li = []
    i = 0
    while fibDynamic(i) <= length+1 :
        li.append(fibDynamic(i))
        i += 1
    li = set(li)
    numJumps = 0
    if length+1 in li : return numJumps + 1
    i = length - 1
    while i >= 0 and not crossed :
        if A[i] :
            if i+1 in li :
                numJumps += 1
                jumpIndexList.append(i)
                if length - i in li : 
                    numJumps += 1
                    crossed = True
                    return numJumps
                numJumps += solution(A[i+1:length])
        i -= 1
    if crossed :
        return numJumps
    if not crossed and len(jumpIndexList) == 0 :
        return -1
    else :
        A[jumpIndexList.pop()] = 0
        if len(jumpIndexList) > 0 :
            return numJumps - 1 + solution(A[jumpIndexList[-1] + 1 : length])
        else : 
            return solution(A)

print solution(A)
