Author: Farzin Fakhraei - ffakhrae - 301125876

Executable File Usage: ./rip.all.in.one [argument] --where argument is in 2..4 and is required.

./rip.all.in.one 2 : answer to question 2
./rip.all.in.one 3 : answer to question 3
./rip.all.in.one 4 : modified version of question 3. It makes "N1" accessible after all tables converge for "N1" inaccessible. 

Included Files:
    rip_all_in_one.cpp: the main is implemented herer
    router.h: header file for class "router" that was implemented to hold members of type "router". Please see the class definition file for available function and precondition/postconditions
    router.cpp: implementation file for the "router" class
    Makefile: used for compiling the source codes. It creates rip.all.in.one (executable).
    log.*.txt: sample run of the program for questions 2, 3, and modified version, on my own machine at home.

Recommended Usage:
    ./rip.all.in.one [int argument] > log.[argument].txt
    (need to press enter after execution so that the program completes its execution)

Since a large number of routing tables are printed (the program prints received advertised table, current routing table, and updated routing table for each router in each round), it's best to store the results in a txt file and view them in a text file editor.
If you are interested in only results for start of each round, search the log file for "Start of Round"
If you are interested only in the final state of the routing tables, search the log file for "End of Convergence"
These parts of the output are visually marked by double lines of "*"s 
********************************************************************************
to set them apart from the details of the process. 


The executable file is tested on cs-vnl and is working properly at the date this document was written. 
However, I used g++ compiler to create the executable on my  own machine. The last time I checked, g++ was not installed on cs-vnl. You could change the COMPILER to gcc in the Makefile, but I haven't done any testing with gcc and cannot verify the results.


Have a beautiful time!

Farzin

