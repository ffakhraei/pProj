#!/bin/env/python

"""Solution is not correct"""



H=[8,8,5,7,9,8,7,4,8]

def solution(H) :
    minNum = 0
    length = len(H)
    minElem = min(H)
    if length == 1 :
        minNum += 1
        return minNum
    li.append(H[0])
    for i in xrange(length-1) :
        if H[i] == H[i+1] :
            continue
        else :
            if H[i+1] < li[0] :
                li[0] = H[i+1] 
                minNum += 1
            else :
                minNum += 1
    return minNum

print solution(H)
