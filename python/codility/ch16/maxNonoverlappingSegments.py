#/bin/env/python

A=[]
B=[]
# expect 0

A=[0]
B=[0]
# expect 1

A=[0,2,100]
B=[0,50,1000]
# expect 3

A=[0,4,8,12,16,20]
B=[4,8,12,16,20,24]

A=[1,3,7,9,9]
B=[5,6,8,9,10]
# expect 3

def solution(A,B) :
    n = len(A)
    if n == 0 : return 0
    if n == 1 : return 1
    res,i = 1,0
    begn = A[i]
    end = B[i]
    begList, endList = [A[i]], [B[i]]
    while i < n-1 :
        while i < n-1 and not (begn <= A[i+1] <= end or A[i+1] <= begn <= B[i+1]) :
            i += 1
            res += 1
            begn = A[i]
            end = B[i]
            begList.append(begn)
            endList.append(end)
        while i < n-1 and (begn <= A[i+1] <= end or A[i+1] <= begn <= B[i+1]) : 
            i += 1 
    return res

print solution(A,B)
