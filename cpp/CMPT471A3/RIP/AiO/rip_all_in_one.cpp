#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

//------------------------------------------------------------------------------
//      CLASS DEFINITIONS
//------------------------------------------------------------------------------

class router
{
    public:

        //----------------------------------------------------------------------
        //      TYPEDEFs and STATIC CONSTants 
        //----------------------------------------------------------------------
        
        static const size_t NUMBER_NETWORKS=7;
        static const size_t NUMBER_ROUTERS=6;
        static const size_t NUMBER_CONNECTTIONS_PER_ROUTER=2;
        static const size_t UNREACHABLE=16;

        //----------------------------------------------------------------------
        //      CONSTRUCTOR(s) 
        //----------------------------------------------------------------------

        router(); 
        // constructor

        router(const char* r_name, const char* l_neighbour, const char* r_neighbour);
        // parametrized class constructor

        //~router();
        //class destructor

        //----------------------------------------------------------------------
        //      MODIFICATION MEMBER FUNCTIONS
        //----------------------------------------------------------------------

        void initialize_routing_table(char* [][3]);
        //POSTCONDITION:
        //Routing table is initialized for directly connected network (number of rows) and 3 columns, with entries:
        //[i][1]: Destination="Ni",
        //[i][2]: Next Hop Router="Direct Delivery"
        //[i][3]: Number of Hops to N(i)="1"

        void advertise(void);
        //POSTCONDITION:
        // router updates the static member "advertised_table" which will be used by its immediate neighbours to update their routing table. 

        void update_routing_table(router sender_router);
        //POSTCONDITION:
        // router updates its routing table based on Bellman-Ford Algorithm

        void set_timer(size_t timer, size_t value);
        //POSTCONDITION:
        // the value of the timer is set to value

        void set_right_neighbour(const char* r_neighbour);
        //POSTCONDITION:
        // set the right neighbour of the router
        
        void set_left_neighbour(const char* l_neighbour);
        //POSTCONDITION:
        // set the right neighbour of the router
        
        void reset_advertised_table(void);
        //POSTCONDITION:
        // advertised table is reset to empty string for all fields

        void set_unreachable(string network);
        //PRECONDITION:
        // "network" is an immediate neighbouring network of the caller router
        //POSTCONDITION
        // number of hops for the destination "network" is set to 16 in the routing table

        void set_reachable(string network);
        //PRECONDITION:
        // "network" is an immediate neighbouring network of the caller router
        //POSTCONDITION:
        // number of hops for the destination "network" is set to 1 and delivery is set to direct
        
        //----------------------------------------------------------------------
        //      CONST FUNCTIONS 
        //----------------------------------------------------------------------
        
        void print_routing_table(void) const;
        //POSTCONDITION:
        // routing table is printed on stdout 

        inline size_t get_timer(size_t timer) const { return timer; }
        //POSTCONDITION:
        // the value of the timer is returned

        inline char* get_left_neighbour(void) const { return left_neighbour; }
        //POSTCONDITION:
        // returns the left neighbour of the router

        inline char* get_right_neighbour(void) const { return right_neighbour; }
        //POSTCONDITION:
        // returns the right neighbour of the router

        inline size_t get_table_size(void) const { return table_size; }
        //POSTCONDITION
        // returns the number of rows in the routing table

        void print_advertised_table(void) const;
        //POSTCONDITION
        // advertised table is printed


        
    private:
        char left_network[3], right_network[3], router_name[3];
        char *left_neighbour, *right_neighbour, *router_name_ptr;
        string routing_table [NUMBER_NETWORKS][3];
        static string advertised_table [NUMBER_NETWORKS][3];
        size_t periodic_timer, expiration_timer, garbage_collection_timer, table_size;
        static size_t advertised_table_size;
};

string router::advertised_table[NUMBER_NETWORKS][3]={"\0"};
size_t router::advertised_table_size=0;

//------------------------------------------------------------------------------
//      CLASS ROUTER FUNCTION DEFINITIONS
//------------------------------------------------------------------------------

router::router()
{
    table_size=0;
}

router::router(const char* r_name, const char* l_neighbour, const char* r_neighbour)
{
    //assigning left and right neighboring networks
    router_name_ptr=router_name;
    left_neighbour=left_network;
    right_neighbour=right_network;
    strcpy(left_neighbour, l_neighbour);
    strcpy(right_neighbour, r_neighbour);
    strcpy(router_name_ptr, r_name);
    
    char next_hop[10]="Direct\0";
    char number_hops[3]="1\0";


    //initializing the routing table
    //strcpy((char*) routing_table, left_neighbour);
    //strcpy((char*) routing_table + 1, (char*) next_hop);
    //strcpy((char*) routing_table + 2, (char*) number_hops);
    routing_table[0][0]=left_neighbour;
    routing_table[0][1]=(char*) next_hop;
    routing_table[0][2]=(char*) number_hops;

    routing_table[1][0]=right_neighbour;
    routing_table[1][1]=(char*) next_hop;
    routing_table[1][2]=(char*) number_hops;

    table_size=2;
}

void router::set_timer(size_t timer, size_t value)
{
    timer=value;
}

void router::set_right_neighbour(const char* r_neighbour)
{
    strcpy(right_neighbour, r_neighbour);
}

void router::set_left_neighbour(const char* l_neighbour)
{
    strcpy(left_neighbour, l_neighbour);
}

void router::print_routing_table(void) const
{
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Routing Table at Router : " << (*this).router_name << endl;
    cout << "____________________________________________________________" << endl;
    cout << "Destination\t Next Hop Router\t Number of Hops\n";
    cout << "------------------------------------------------------------" << endl;
    for ( size_t i=0; i < (*this).table_size; ++i )
    {
        for (size_t j=0; j < 3; ++j)
            cout << (*this).routing_table[i][j] << "\t\t       ";
        cout << endl;
    }
    cout << "____________________________________________________________" << endl;
}

void router::print_advertised_table(void) const
{
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Advertised Table at Router : " << (*this).router_name << endl;
    cout << "____________________________________________________________" << endl;
    cout << "Destination\t Next Hop Router\t Number of Hops\n";
    cout << "------------------------------------------------------------" << endl;
    for ( size_t i=0; i < advertised_table_size; ++i )
    {
        for (size_t j=0; j < 3; ++j)
            cout << advertised_table[i][j] << "\t\t       ";
        cout << endl;
    }
    cout << "____________________________________________________________" << endl;
}

void router::reset_advertised_table(void)
{
    for ( size_t i=0; i < router::NUMBER_NETWORKS; ++i )
    {
        for (size_t j=0; j < 3; ++j)
            advertised_table[i][j]="\0";
    }
    advertised_table_size=0;
}

void router::advertise(void)
{
    reset_advertised_table();
    advertised_table_size=this->table_size;
    for ( size_t i=0; i < (*this).table_size; ++i )
    {
        for (size_t j=0; j < 3; ++j)
            advertised_table[i][j]=(*this).routing_table[i][j];
    }
}

void router::update_routing_table(router sender_router)
{
    bool found=false;
    string next_hop_router=sender_router.router_name;
    
    for (size_t i=0; i < advertised_table_size; ++i) 
    {
        found=false;
        for (size_t j=0; j < this->table_size; ++j)
        {
            if ((advertised_table[i][0] == this->routing_table[j][0])) 
            {  
                int current_distance=atoi((this->routing_table[j][2]).c_str());
                int advertised_distance=atoi((advertised_table[i][2]).c_str());
                found=true;

                if ((this->routing_table[j][1] != "Direct"))
                {
                    if (current_distance > (1 + advertised_distance))
                    {
                        int distance=1 + advertised_distance;
                           if (distance > 16)
                            distance=16;
                        stringstream ss;
                        ss << distance;
                        this->routing_table[j][2]=ss.str();
                        this->routing_table[j][1]=next_hop_router;
                    }

                    if (this->routing_table[j][1] == next_hop_router)
                        if (current_distance != 1 + advertised_distance)
                        {
                            int distance=1 + advertised_distance;
                            if (distance > 16)
                                distance=16;
                            stringstream ss;
                            ss << distance;
                            this->routing_table[j][2]=ss.str();
                        }
                }
            }
        }

        if (!found)
        {
            assert(this->table_size <= NUMBER_NETWORKS);
            int distance=1 + atoi((advertised_table[i][2]).c_str());
            stringstream ss;
            ss << distance;
            this->routing_table[this->table_size][0]=advertised_table[i][0];
            this->routing_table[this->table_size][1]=sender_router.router_name;
            this->routing_table[this->table_size][2]=ss.str();
            this->table_size +=1;
            
        }
    }
}

void router::set_unreachable(string network)
{
    bool not_found=true;

    for (size_t i=0; i < this->table_size; ++i)
        if (this->routing_table[i][0] == network)
        {
            this->routing_table[i][2]="16";
            not_found=false;
            break;
        }

    assert(this->table_size < NUMBER_NETWORKS);

    if(not_found)
    {
        this->routing_table[table_size][0]=network;
        this->routing_table[table_size][1]="*";
        this->routing_table[table_size][2]="16";

        this->table_size += 1;
    }
}

void router::set_reachable(string network)
{
    bool not_found=true;

    for (size_t i=0; i < this->table_size; ++i)
        if (this->routing_table[i][0] == network)
        {
            this->routing_table[i][2]="1";
            not_found=false;
            break;
        }

    if(not_found)
    {
        assert(this->table_size < NUMBER_NETWORKS);

        this->routing_table[table_size][0]=network;
        this->routing_table[table_size][1]="Direct";
        this->routing_table[table_size][2]="1";

        this->table_size += 1;
    }
}
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
    for (size_t convergence=0; convergence < num_rounds_to_converge; ++convergence)
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
