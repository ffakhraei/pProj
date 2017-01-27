#!/bin/env/python

A="{[()()]}"
B="([)()]"
C="{[()()[]]}"
D="()[cb.\"()]"
E="(((()"
F="{{{}"


def solution(S) :
    stripped = []
    keys = ["[", "{", "(", ")", "}", "]"] 
    reference = ["[]", "{}", "()"]
    if S == "" :
        return 1
    for i, item in enumerate(S) :
        if item in keys :
            stripped.append(item) 
            if len(stripped) > 1 :
                if stripped[-2]+stripped[-1] in reference :
                    stripped.pop(-2)
                    stripped.pop(-1)
    length = len(stripped)
    if length == 0 :
        return 1
    elif length%2 != 0 :
        return 0
    else :
            while(stripped) :
                left = stripped.pop(0)
                right = stripped.pop()
                if left + right not in reference :
                    return 0

print solution(A)
print solution(B)
print solution(C)
print solution(D)
print solution(E)
print solution(F)
