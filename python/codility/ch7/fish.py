#!/bin/env/python

from collections import deque
#A=[4,3,2,1,5]
#B=[0,1,0,0,0]

A=[6,0,3,7,5,4]
B=[1,1,1,0,1,1]

def solution(A,B):
    length = len(A)
    if length == 0 :
        return 0
    if length == 1 :
        return 1
    fishTupleDeque = deque(zip(A,B))
    resultList = []
    finished = False
    def moveUpStream(fish, fishList=fishTupleDeque, li=resultList) :
        while len(li) > 0 and li[-1][1] == 1 and fish > li[-1]:
                li.pop()
        if len(li) == 0 :
            li.append(fish)
        elif li[-1][1] == 0 :
            li.append(fish)
            finished = True
        else :
            fish = li.pop()
            moveDownStream(fish)
    def moveDownStream(fish, fishList=fishTupleDeque, li=resultList) :
        while len(fishList) > 0 and fishList[0][1] == 0 and fish > fishList[0] :
            fishList.popleft()
        if len(fishList) == 0 :
            li.append(fish)
            finished = True
        elif fishList[0][1] == 1 :
            li.append(fish)
            moveDownStream(fishList.popleft())
        else :
                moveUpStream(fishList.popleft())
    def move(T, li, la) :
        if T[1] == 0 :
            moveUpStream(T, li, la)
        else :
            moveDownStream(T, li, la)
    while not finished and len(fishTupleDeque) > 0:
        move(fishTupleDeque.popleft(),fishTupleDeque, resultList)
    return len(resultList)

#import pdb; pdb.set_trace()
print solution(A,B)
