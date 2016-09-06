// router.h     author: Farzin Fakhraei
#ifndef ROUTER_H
#define ROUTER_H

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
        int trigger;

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

#endif
