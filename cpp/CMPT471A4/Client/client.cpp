#include <arpa/inet.h>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXDATASIZE 1000 // max number of bytes we can get at once

using namespace std;


//------------------------------------------------------------------------------
//  GLOBAL VARIABLES
//------------------------------------------------------------------------------

const int PUBLIC_PRIME=11;
const int PUBLIC_BASE=2;   //primitive root of PUBLIC_PRIME
const size_t MAXIMUM_MESSAGE_LENGTH=100;
int key=0;


//------------------------------------------------------------------------------
//  MAIN FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

void *get_in_addr(struct sockaddr *sa);
//POSTCONDITION:
// sockaddr (either IPv4 or IPv6 is stored in a struct sockaddr pointed to by pointer "sa"

int choose_private_number(int PUBLIC_PRIME);
// POSTCONDITION:
// a random integer in the range [1, PUBLIC_PRIME-1] is returned 

int calculate_public_value(int x_private_number, int PUBLIC_PRIME, int PUBLIC_BASE);
// POSTCONDITION:
// the intermediate value to be sent to the other host is returned

int calculate_key(int xx_public_value, int x_private_number, int PUBLIC_PRIME);
// POSTCONDITION:
// the final shared key is calculated and returned

void encrypt_ROT(char* msg_ptr, int key);
// POSTCONDITION:
// the message is encrypted using ROT-key (generated and exchanged using D-H Algorithm
//  it is also known as caeser's cypher

void decrypt_ROT(char* msg_ptr, int key);
// POSTCONDITION:
// message is decrypted using ROT-key. It's the inverse of the encrypt_ROT function


//------------------------------------------------------------------------------
//  MAIN BODY
//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int sockfd, numbytes; 
    char buf[MAXDATASIZE];
    struct addrinfo hints, *server_info, *server_info_ptr;
    int return_value;
    char server_IP[INET6_ADDRSTRLEN];
    char message[MAXDATASIZE]={'\0'};
    char *msg_ptr=message;
    string message_str="hello";
    
    //variables for Diffie-Hellman:
    int client_private_number;
    int client_public_value;
    int server_public_value;
    int client_key;

    system("clear");

    if (argc != 3)
    {
        cerr << "Usage: ./client host_IP port_number\n";
        return EXIT_FAILURE;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    if ((return_value = getaddrinfo(argv[1], argv[2], &hints, &server_info)) != 0)
    {
        cerr << "Getting host IP: " << gai_strerror(return_value) << endl;
        return EXIT_FAILURE;
    }
    
    for(server_info_ptr = server_info; server_info_ptr != NULL; server_info_ptr = server_info_ptr->ai_next)
    {

        if ((sockfd = socket(server_info_ptr->ai_family, server_info_ptr->ai_socktype, server_info_ptr->ai_protocol)) == -1)
        {
            perror("Client Process: socket() Error");
            continue;
        }

        if (connect(sockfd, server_info_ptr->ai_addr, server_info_ptr->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("Client Process: connect() Error");
            continue;
        }

        break;
    }

    if (server_info_ptr == NULL)
    {
        cerr << "Client Process: Connection to host failed\n";
        return EXIT_FAILURE;
    }

    inet_ntop(server_info_ptr->ai_family, get_in_addr((struct sockaddr *)server_info_ptr->ai_addr), server_IP, sizeof server_IP);

    system("clear");
    cout << "Client is connecting to server " << server_IP << " " << argv[2] << endl;
    if (send(sockfd, "This is message is not encrypted...", 36, 0) == -1)
        perror("Client Process: send() Error");
    cout << endl << "Initializing Diffie-Hellman key exchange...\n";

    client_private_number=choose_private_number(PUBLIC_PRIME); 
    cout << "client private number: " << client_private_number << endl;
    client_public_value=calculate_public_value(client_private_number, PUBLIC_PRIME, PUBLIC_BASE);
    cout << "client public value: " << client_public_value << endl;

    cout << "sending client public value...\n";
    stringstream ss;
    ss << client_public_value;
    message_str = ss.str();
    msg_ptr=(char*) message_str.c_str();    
    if (send(sockfd, msg_ptr, 100, 0) == -1)
    {
        perror("Client Process: send() Error");
        return EXIT_FAILURE;
    }

    cout << "receiving server public value...\n";
    for (size_t i=0; i < MAXDATASIZE; ++i)
        buf[i]='\0';
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
    {
        perror("Client Process: recv() Error");
        return EXIT_FAILURE;
    }
    buf[numbytes]='\0';

    server_public_value=atoi(buf);
    cout << "received server public value: " << server_public_value << endl;

    cout << "calculating client key...\n";
    client_key=calculate_key(server_public_value, client_private_number, PUBLIC_PRIME);

    cout << "client key: " << client_key << endl << endl << endl;

    while (message_str != "")
    {

        cout << "Enter a message to send to servere (less than 100 characters). Press Enter and send an empty line to disconnect from the server:\n";
        //cin.ignore();
        getline(cin, message_str);
        msg_ptr=(char*) message_str.c_str();

        encrypt_ROT(msg_ptr, client_key);

        if (send(sockfd, msg_ptr, 110, 0) == -1)
        {
            cerr << "could not send Error.";
            perror("Client Process: send() Error");
            continue;
        }
    }

    freeaddrinfo(server_info); 
    
    close(sockfd);

    return EXIT_SUCCESS;
}
  
//------------------------------------------------------------------------------
//  MAIN FUNCTION DEFINITIONS
//------------------------------------------------------------------------------

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int choose_private_number(int PUBLIC_PRIME)
{
    srand(time(NULL)); 
    return ((rand()%(PUBLIC_PRIME-2))+1);
}

int calculate_public_value(int x_private_number, int PUBLIC_PRIME, int PUBLIC_BASE)
{
    return (fmod(pow(PUBLIC_BASE, x_private_number), static_cast<double>(PUBLIC_PRIME)));
}


int calculate_key(int xx_public_value, int x_private_number, int PUBLIC_PRIME)
{
    return (fmod(pow(xx_public_value, x_private_number), static_cast<double>(PUBLIC_PRIME)));
}


void encrypt_ROT(char* msg_ptr, int key)
{
    size_t length=strlen(msg_ptr);

    for (size_t i=0; i < length; ++i)
    {
        *msg_ptr=static_cast<char>((static_cast<int>(*msg_ptr)+key)%128);
        ++msg_ptr;
    }
}

void decrypt_ROT(char* msg_ptr, int key)
{
    size_t length=strlen(msg_ptr);

    for (size_t i=0; i < length; ++i)
    {
        *msg_ptr=static_cast<char>((static_cast<int>(*msg_ptr)-key)%128);
        ++msg_ptr;
    }
}
