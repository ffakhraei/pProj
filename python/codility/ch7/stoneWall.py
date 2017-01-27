#!/bin/env/python

""" works as intended -- 

Algorithm for solution is incorrect.

    only works in special cases.

"""

H=[3,2,1]
H=[8,8,5,7,9,8,7,4,8]

import functools

global islandList, counter 
islandList = []
counter = 0
def group(H) :
    li = []
    result = []
    global counter
    for i, item in enumerate(H) :
        if item > 0 :
            li.append(item)
        else :
            if i < len(H) - 1 :
                if H[i+1] == 0 :
                    continue
                else :
                    counter += 1
            else :
                counter += 1
            if len(li) > 0 :
                result.append(li)
            li = []
    if len(li) > 0 :
        result.append(li)
    return result

def foo(a, b) : return a - b

def crumble(myList) :
    return map(functools.partial(foo, b=min(myList)), myList)

def solution(H) :
    global islandList
    global counter

    if len(H) == 0 :
        return 0
    islands = [H]
    #crumbled = crumble(H)
    #islands = group(crumbled)
    while len(islands) > 0 :
        while len(islands) > 1 :
            islandList.append(islands.pop())
        crumbled = crumble(islands[0])
        islands = group(crumbled)
    if len(islandList) > 0 :
        solution(islandList.pop())
    return counter

print solution(H)
