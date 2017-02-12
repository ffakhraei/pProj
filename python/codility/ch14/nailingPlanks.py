#/bin/env/python

A=[1,4,5,8]
B=[4,5,9,10]
C=[4,4,4,4,6,7,6,6,4,7,3,6,4,7,4,10,2]
#expect 16
A=[2]
B=[2]
C=[2]
#expect 1
A=[2]
B=[2]
C=[1]
#expect -1
A=[1,4,5,8]
B=[4,5,9,10]
C=[4,6,7,10,2]
#expect 4

def solution(A, B, C) :
    n = len(A)
    numNails = 0
    numBoards = n
    li = n * [1]
    for i,item in enumerate(C) :
        if numBoards > 0 :
            numNails += 1
        for j in xrange(len(A)) :
            if j >= len(A) :
                break
            if item in xrange(A[j], B[j]+1) :
                if li[j] :
                    li[j] = 0
                    numBoards -= 1
    for i in li :
        if i :
            return -1
    else : return numNails

print solution(A,B,C)
