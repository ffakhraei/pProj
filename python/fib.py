#!/usr/bin/env python
import sys

if __name__ == "__main__":
    def fib(arg):
        """
        function fib:
        precondition: takes an integer argument
        postcondition: returns the fibonacci number of the argument
       
        usage: python fib.py arg
        """    
        
        if arg == 1:
            return 1
        if arg == 0:
            return 1

        if arg > 1:
            return fib(arg - 2) + fib(arg - 1)
    if len(sys.argv) > 1:
        print fib(int(sys.argv[1]))
