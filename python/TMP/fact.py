#!/usr/bin/env python
import sys

if __name__ == "__main__":
    def fact(arg):
        """
        function fact:
        precondition: takes a non negative integer argument
        postcondition: returns the factorial of the argument
       
        usage: python fact.py arg
        """    
        
        if arg == 1:
            return 1
        if arg == 0:
            return 1

        if arg > 1:
            return fact(arg - 1) * arg
    if len(sys.argv) > 1:
        print fact(int(sys.argv[1]))
