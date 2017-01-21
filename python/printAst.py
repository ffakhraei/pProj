#!/usr/bin/env python
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "Wrong Usage"
        exit(1) 

# DEBUG 
    print sys.argv
# DEBUG END

    arg = int(sys.argv[1])

    def printAst(arg):
        """
        function fact:
        precondition: takes a non negative integer argument
        postcondition: returns the factorial of the argument
       
        usage: python fact.py arg
        """    
        for i in range(arg, 0, -1): 
            print 2*(arg-i)*' ', (2*i-1)*'* ' 

    printAst(arg)            
