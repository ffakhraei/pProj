#!/bin/env/python
binRep = bin(N)
binRepStr = binRep[2:]
tempMax = 0
realMax = 0

for i in xrange(len(binRepStr)-1):
    if binRepStr[i] == '1':
        continue
    if binRepStr[i] == '0':
        tempMax += 1
        if binRepStr[i+1] == '1':
            if tempMax > realMax:
                realMax = tempMax
            tempMax = 0
print realMax
