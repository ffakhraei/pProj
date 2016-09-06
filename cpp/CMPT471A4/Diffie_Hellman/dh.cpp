// dh.cpp

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>

using namespace std;


//------------------------------------------------------------------------------
//  GLOBAL VARIABLES
//------------------------------------------------------------------------------
const int PUBLIC_PRIME=23;
const int PUBLIC_BASE=5;   //primitive root of PUBLIC_PRIME
const size_t MAXIMUM_MESSAGE_LENGTH=101;


//------------------------------------------------------------------------------
//  FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

int choose_private_number(int PUBLIC_PRIME);
// POSTCONDITION:
// a random integer in the range [1, PUBLIC_PRIME-1] is returned 

int calculate_public_value(int x_private_number, int PUBLIC_PRIME, int PUBLIC_BASE);
// POSTCONDITION:
// the intermediate value to be sent to the other host is returned

int calculate_key(int xx_public_value, int x_private_number, int PUBLIC_PRIME);
// POSTCONDITION:
// the final shared key is calculated and returned

void encrypt(char* msg_ptr, int key);
// POSTCONDITION:
// the message is encrypted using ROT-key (generated and exchanged using D-H Algorithm
//  it is also known as caeser's cypher

void decrypt(char* msg_ptr, int key);
// POSTCONDITION:
// message is decrypted using ROT-key. It's the inverse of the encrypt function


//------------------------------------------------------------------------------
//  MAIN BODY  
//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    system("clear");
    int alice_private_number;
    int bob_private_number;
    int alice_public_value;
    int bob_public_value;
    int alice_key, bob_key, key;
    char message[MAXIMUM_MESSAGE_LENGTH]="This is a test of encrypting messages!!!";
    char* msg_ptr=message;

    alice_private_number=choose_private_number(PUBLIC_PRIME);
    //alice_private_number=15;
    bob_private_number=choose_private_number(PUBLIC_PRIME);
    //bob_private_number=13;

    while (bob_private_number == alice_private_number)
        bob_private_number=choose_private_number(PUBLIC_PRIME);

    alice_public_value=calculate_public_value(alice_private_number, PUBLIC_PRIME, PUBLIC_BASE);
    bob_public_value=calculate_public_value(bob_private_number, PUBLIC_PRIME, PUBLIC_BASE);

    alice_key=calculate_key(bob_public_value, alice_private_number, PUBLIC_PRIME);
    bob_key=calculate_key(alice_public_value, bob_private_number, PUBLIC_PRIME);

    key=alice_key;

    cout << pow(PUBLIC_BASE, alice_private_number) << endl;
    cout << "alice private: " << alice_private_number << " bob private: " << bob_private_number << endl;
    cout << "alice public: " << alice_public_value << " bob public: " << bob_public_value << endl;
    cout << "alice key: " << alice_key << " bob key: " << bob_key << endl;
    cout << msg_ptr << endl;

    encrypt(msg_ptr, key);

    cout << "the encrypted message is: " << msg_ptr << endl;
    cout << endl;

    decrypt(msg_ptr, key);
    cout << "the decrypted message is: " << msg_ptr << endl;

    
    return EXIT_SUCCESS;
}


//------------------------------------------------------------------------------
//  FUNCTION DEFINITIONS
//------------------------------------------------------------------------------

int choose_private_number(int PUBLIC_PRIME)
{
    srand(time(0)); //changing the random number seed 
    //system("wait 2");
    return ((rand()%(PUBLIC_PRIME-2))+1);
}

int calculate_public_value(int x_private_number, int PUBLIC_PRIME, int PUBLIC_BASE)
{
    return (fmod(pow((double) PUBLIC_BASE, (double) x_private_number), static_cast<double>(PUBLIC_PRIME)));
}


int calculate_key(int xx_public_value, int x_private_number, int PUBLIC_PRIME)
{
    return (fmod(pow((double) xx_public_value, (double) x_private_number), static_cast<double>(PUBLIC_PRIME)));
}


void encrypt(char* msg_ptr, int key)
{
    size_t length=strlen(msg_ptr);

    for (size_t i=0; i < length; ++i)
    {
        *msg_ptr=static_cast<char>((static_cast<int>(*msg_ptr)+key)%128);
        ++msg_ptr;
    }
}

void decrypt(char* msg_ptr, int key)
{
    size_t length=strlen(msg_ptr);

    for (size_t i=0; i < length; ++i)
    {
        *msg_ptr=static_cast<char>((static_cast<int>(*msg_ptr)-key)%128);
        ++msg_ptr;
    }
}
