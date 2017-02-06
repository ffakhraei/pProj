#/bin/env/python

A=[3,1,2,3,6]

def solution(A) :
    length = len(A)
    S = {}
    result = []
    i = 0
    while i < length :
        counter = 0
        j = 0
        if A[i] not in S : 
            while j < length :
                if A[i] % A[j] != 0 :
                    counter += 1
                j += 1
            S[A[i]] = counter
            result.append(counter)
            j = 0
        else : result.append(S[A[i]])
        i += 1
    return result

print solution(A)
