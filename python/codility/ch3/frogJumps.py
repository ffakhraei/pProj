#!/bin/env/python
X=10
Y=85
D=30

def solution(X, Y, D):
    distance=Y-X
    if distance%D != 0:
        return distance//D + 1
    else:
        return distance//D
print solution(X, Y, D)

