#!/env/bin/python

A=[-3,1,2,-2,5,6]
B=[-3,2,-2,5,6]
C=[-1,1,1,-2,-1,6]
D=[-3,1,2]
E=[-1,0,1]
F=[0,1,2]
G=[0,3,5,8]


def solution(A):
    A.sort()
    maxProduct = A[0] * A[1] * A[2]
    negList = [x for x in A if x < 0]
    posList = [x for x in A if x >= 0]
    negLen = len(negList)
    posLen = len(posList)
    if negLen > 1 and posLen > 0 :
        if maxProduct < negList[0] * negList[1] * posList[-1] :
            maxProduct = negList[0] * negList[1] * posList[-1]
    if negLen > 2 :
        if maxProduct < negList[-1] * negList[-2] * negList[-3] :
            maxProduct = negList[-1] * negList[-2] * negList[-3]
    if posLen > 2 :
        if maxProduct < posList[-1] * posList[-2] * posList[-3] :
            maxProduct = posList[-1] * posList[-2] * posList[-3]
    return maxProduct

print solution(A)
print solution(B)
print solution(C)
print solution(D)
print solution(E)
print solution(F)
print solution(G)
