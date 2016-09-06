#include <arpa/inet.h>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXDATASIZE 1000 // max number of bytes we can get at once

using namespace std;

//------------------------------------------------------------------------------
//  MAIN FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

void *get_in_addr(struct sockaddr *sa);
//POSTCONDITION:
// sockaddr (either IPv4 or IPv6 is stored in a struct sockaddr pointed to by pointer "sa"


//------------------------------------------------------------------------------
//  MAIN
//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int sockfd, numbytes; //, yes=1;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *server_info, *server_info_ptr;
    int return_value;
    char server_IP[INET6_ADDRSTRLEN];
    char message[MAXDATASIZE]={'\0'};
    char *msg_ptr=message;
    string message_str="hello";
    //string *str_ptr=&message_str;
    
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

    cout << "Client is connecting to server " << server_IP << endl;

    if (send(sockfd, "Hello, server", 14, 0) == -1)
        perror("Client Process: send() Error");

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
    {
        perror("Client Process: recv() Error");
        return EXIT_FAILURE;
    }

    buf[numbytes] = '\0';
    cout << "Client Process: Received the following message from: " << server_IP << " " << argv[2] << endl << buf << endl;

    while (message_str != "")
    {
        cout << "Enter a message to send to servere (less than 100 characters). Press Enter and send an empty line to disconnect from the server:\n";
        //cin >> msg_ptr;
        //cout << msg_ptr << " that was msg_ptr\n";
        //cout << "enter the string now: ";
        //cin.ignore();
        getline(cin, message_str);
        //cin >> message_str;
        //cout << endl << message_str << " this is the string\n";

        msg_ptr=(char*) message_str.c_str();

        if (send(sockfd, msg_ptr, 110, 0) == -1)
        {
            cerr << "could not send Error.";
            perror("Client Process: send() Error");
            continue;
        }
        
        //for (size_t i=0; i < MAXDATASIZE; ++i)
            //message[i]='\0';

        //cout << "Send another message? [1 to continue | 0 to abort]: ";
        //cin >> yes;
    }

    freeaddrinfo(server_info); 
    

    close(sockfd);

    return EXIT_FAILURE;
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
