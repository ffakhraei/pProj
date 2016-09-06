// rip_all_in_one.cpp      author: Farzin Fakhraei
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "router.h"

using namespace std;


//------------------------------------------------------------------------------
//      MAIN FUNCTION PROTOTYPES 
//------------------------------------------------------------------------------

void initialize_routers(router router_list[], const char* NETWORK_LIST[], const char* ROUTER_LIST[], const size_t NUMBER_ROUTERS);
//POSTCONDITION:
// routers in route_list have been initialized, their left and righ neighbouring networks have been
// set, the initial routing table is set, initial routing table is also printed on stdout

void start_rip(router router_list[], const size_t NUMBER_ROUTERS, size_t num_rounds_to_converge);
//PRECONDITION:
//  routers in router_list must have been initialized prior to calling this function
//POSTCONDITION:
// routers in router_list send and receive RIP advertisements for num_rounds_to_converge.
// at the beginning and end of each round, routing table of all routers is printed
// for the advertisement and update process, the current routing table, the advertised routing 
// table, and the updated routing table is printed for the neighbourin router(s) of each router
// in router_list
// final state of the routing tables for all routers is printed once each and every router
// has finished advertising and updating for num_rounds_to_converge.

// NOTE:
// it is up to the user of the function to determine a reasonable num_rounds_to_converge
// so that all routing tables, converge. Based on my trials, it is usually at least equal to 
// NUMBER_NETWORKS in the AS network; so it is a good practice to set num_rounds_to_converge
// equal to NUMBER_NETWORKS and observe the results and make fine tune adjustments based on 
// those results.

//------------------------------------------------------------------------------
//      MAIN BODY
//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        cout << "Error: Usage ./rip.all.in.one [2, or 3, or 4]" << endl;
        return EXIT_FAILURE;
    }

    assert(argc == 2);

    int input_argument;
    
    if (atoi(argv[1]) == 2)
        input_argument=2;
    else if (atoi(argv[1]) == 3)
        input_argument=3;
    else if (atoi(argv[1]) == 4)
        input_argument=4;
    else
    {
        cout << "\vWrong input argument provided. Legal values are 2, 3, or 4.\v\n";
        return EXIT_FAILURE;
    }

    
    const size_t NUMBER_ROUTERS=6;
    const size_t NUMBER_NETWORKS=7;

    const char* NETWORK_LIST[NUMBER_NETWORKS]={"N1", "N2", "N3", "N4", "N5", "N6", "N7"};
    const char* ROUTER_LIST[NUMBER_ROUTERS]={"R1", "R2", "R3", "R4", "R5", "R6"};

    // an array of type "router" to hold NUMBER_ROUTERS routers
    router router_list[NUMBER_ROUTERS];
    
    initialize_routers(router_list, NETWORK_LIST, ROUTER_LIST, NUMBER_ROUTERS);
    
    cout << endl << "\v" << endl;

    switch (input_argument)
    {
        case 2:
            system("clear");
            cout << "This program is for question 2 of the assignment. Press enter to continue...\n";
            cin.get();
            start_rip(router_list, NUMBER_ROUTERS, 7);
            break;
        case 3: 
            system("clear");
            cout << "This program is for question 3 of the assignment. Press enter to continue...\n";
            cin.get();
            //first round of advertisement with network N1 still reachable
            start_rip(router_list, NUMBER_ROUTERS, 1);
            //making N1 unreachable
            router_list[0].set_unreachable("N1");
            //advertising for 7 rounds until all tables converge
            start_rip(router_list, NUMBER_ROUTERS, 7);
            break;
        case 4:
            system("clear");
            cout << "This program is modified version of question 3:\n";
            cout << "It makes N1 unreachable, and after all tables converge, makes it reachable again, and sends RIP messages until all routing tables converge.\n";
            cout << "Press enter to continue...\n";
            cin.get();
            //first round of advertisement with network N1 still reachable
            start_rip(router_list, NUMBER_ROUTERS, 1);
            //making N1 unreachable
            router_list[0].set_unreachable("N1");
            //advertising for 7 rounds until all tables converge
            start_rip(router_list, NUMBER_ROUTERS, 7);

            //making N1 reachable
            router_list[0].set_reachable("N1");
            //advertising for 7 rounds until all tables converge
            start_rip(router_list, NUMBER_ROUTERS, 7);
            break;
    }
    

    return EXIT_SUCCESS;

}

//------------------------------------------------------------------------------
//      MAIN FUNCTION DEFINITIONS      
//------------------------------------------------------------------------------

void initialize_routers(router router_list[], const char* NETWORK_LIST[], const char* ROUTER_LIST[], const size_t NUMBER_ROUTERS)
{
    for (size_t i=0; i < NUMBER_ROUTERS; ++i)
    {
        cout << endl;
        cout << "Initializing Router: " << ROUTER_LIST[i] << " . . .  _ _ _ . . . " << endl;
        router_list[i]=router(ROUTER_LIST[i], NETWORK_LIST[i], NETWORK_LIST[i+1]);
        router_list[i].print_routing_table();
        //router_list[i].advertise();
        //router_list[i].print_advertised_table();
    }
}
void start_rip(router router_list[], const size_t NUMBER_ROUTERS, size_t num_rounds_to_converge)
{
    int number_of_updates=0;
    int convergence=0;

    for (size_t i=0; i < NUMBER_ROUTERS; ++i)
    {
        if (router_list[i].trigger == 1)
        {
            number_of_updates=1;
            break;
        }
    }

    while (number_of_updates == 1)
    {
        cout << endl;
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";
        cout << "Routing Tables at the Start of Round " << convergence+1 << endl;
        
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";
        for (size_t i=0; i < NUMBER_ROUTERS; ++i)
        {
            cout << endl;
            router_list[i].print_routing_table();
        }
        cout << endl;
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";

        cout << endl << endl << endl << "Starting the RIP Sequence....\n" << endl << endl;

        for (size_t i=0; i < NUMBER_ROUTERS; ++i)
        {
            if (i == 0)
            {
                cout << "\n>>>>>>>>>>>>>>>Router R" << i+1 << " is advertising:\n";
                router_list[i].advertise();

                cout << "\nThe advertised routing table is: \n";
                router_list[i].print_advertised_table();

                cout << "\nRouter R" << i+2 << " is going to update its current routing table: " << endl;
                
                cout << "\nCurrent routing table: \n";
                router_list[i+1].print_routing_table();
                router_list[i+1].update_routing_table(router_list[i]);
                cout << "\nThe updated routing table: \n";
                router_list[i+1].print_routing_table();
            }

            else if (i == 5)
            {
                cout << "\n>>>>>>>>>>>>>>>Router R" << i+1 << " is advertising:\n";
                router_list[i].advertise();
                
                cout << "\nThe advertised routing table is: \n";
                router_list[i].print_advertised_table();

                cout << "\nRouter R" << i << " is going to update its current routing table: " << endl;
                
                cout << "\nCurrent routing table: \n";
                router_list[i-1].print_routing_table();
                router_list[i-1].update_routing_table(router_list[i]);
                cout << "\nThe updated routing table: \n";
                router_list[i-1].print_routing_table();
            }

            else
            {
                cout << "\n>>>>>>>>>>>>>>>Router R" << i+1 << " is advertising:\n";
                router_list[i].advertise();

                cout << "\nThe advertised routing table is: \n";
                router_list[i].print_advertised_table();

                cout << "\nRouter R" << i << " is going to update its current routing table: " << endl;
                
                cout << "\nCurrent routing table: \n";
                router_list[i-1].print_routing_table();
                router_list[i-1].update_routing_table(router_list[i]);
                cout << "\nThe updated routing table: \n";
                router_list[i-1].print_routing_table();

                cout << "\nRouter R" << i+2 << " is going to update its current routing table: " << endl;

                cout << "\nCurrent routing table: \n";
                router_list[i+1].print_routing_table();
                router_list[i+1].update_routing_table(router_list[i]);
                cout << "\nThe updated routing table: \n";
                router_list[i+1].print_routing_table();
            }
        }

        ++convergence;

        for (size_t i=0; i < NUMBER_ROUTERS; ++i)
        {
            if (router_list[i].trigger == 1)
            {
                number_of_updates=1;
                break;
            }

            number_of_updates=0;
        }

        if (number_of_updates == 0)
            break;
    }
        
        cout << endl;
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";
        cout << "Routing Tables at the End of the Convergence: " << endl;
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";
        for (size_t i=0; i < NUMBER_ROUTERS; ++i)
        {
            cout << endl;
            router_list[i].print_routing_table();
        }
        cout << endl;
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";
        cout << "********************************************************************************\n";
    
}
