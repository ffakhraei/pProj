#/bin/env/python

A=[-5,-3,-1,0,3,6]

from itertools import imap

def solution(A) :
    return len(set(imap(abs, A)))

print solution(A)
