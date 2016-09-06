// router.cpp     author: Farzin Fakhraei
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
//      CLASS ROUTER IMPLEMENTATION
//------------------------------------------------------------------------------

string router::advertised_table[NUMBER_NETWORKS][3]={"\0"};
size_t router::advertised_table_size=0;

router::router()
{
    table_size=0;
    trigger=1;
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

    trigger=1;
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
        this->trigger=0;
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
                        this->trigger=1;
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
                            this->trigger=1;
                        }
                }
            }
        }

        if (!found)
        {
            assert(this->table_size < NUMBER_NETWORKS);
            int distance=1 + atoi((advertised_table[i][2]).c_str());
            stringstream ss;
            ss << distance;
            this->routing_table[this->table_size][0]=advertised_table[i][0];
            this->routing_table[this->table_size][1]=sender_router.router_name;
            this->routing_table[this->table_size][2]=ss.str();
            this->table_size +=1;
            this->trigger=1;
            
        }
    }
}

void router::set_unreachable(string network)
{
    bool not_found=true;

    for (size_t i=0; i < this->table_size; ++i)
    {
        if (this->routing_table[i][0] == network)
        {
            this->routing_table[i][2]="16";
            not_found=false;
            break;
        }
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
