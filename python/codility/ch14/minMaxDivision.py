#/bin/env/python

A=[2,1,5,1,2,2,2]
K=3 #number of blocks
M=5 #maximum element value
#expect 6

A=[5,3]
K=2 #number of blocks
M=5 #maximum element value
#expect 5

A=[3,2,1]
K=3 #number of blocks
M=3 #maximum element value
#expect 3

A=[4,1,2,7]
K=2 #number of blocks
M=7 #maximum element value
#expect 7

A=[5,2,3,4,6]
K=3 #number of blocks
M=6 #maximum element value
#expect 7

A=[999,999,999]
K=3 #number of blocks
M=1000 #maximum element value
#expect 999

A=[1,3,1,3,2,1,3]
K=3 #number of blocks
M=3 #maximum element value
#expect 5

A=[3,4,5,6,7,8]
K=4 #number of blocks
M=10 #maximum element value
#expect 11

def solution(K, M, A) :
    n = len(A)
    totalSum = sum(A)
    if K == 1 or n == 1 : return totalSum
    minLargeSum = totalSum
    if n == 2 : return min(totalSum, max(A))
    minBlockLength = n // K
    return minLargeSum

print solution(K, M, A)
