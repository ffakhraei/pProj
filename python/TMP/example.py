#!/usr/bin/env python
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "Wrong Usage"
        exit(1) 

    #arg = int(sys.argv[1])
    arg = sys.argv[1]

    def printAst(arg):
        """
        function fact:
        precondition: takes a non negative integer argument
        postcondition: returns the factorial of the argument
       
        usage: python fact.py arg
        """    
        tempMax = 0
        realMax = 0
        for i in arg:
            if i == '0':
                tempMax+=1
                if tempMax > realMax:
                    realMax = tempMax
            else:
                tempMax = 0
        print realMax

    printAst(arg)            
