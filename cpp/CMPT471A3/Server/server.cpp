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
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define BACKLOG 1       //number of pending connections in the queue
#define MAXDATASIZE 1000 // max number of bytes that can be transmitted at once

using namespace std;



//------------------------------------------------------------------------------
//  MAIN FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

void sigchld_handler(int s);
//POSTCONDITION:
// all dead processes are terminated

void* get_in_addr(struct sockaddr* sa);
//POSTCONDITION:
//  IPv4 or IPv6 "sockaddr" is stored in a variable of type sockaddr, pointed to by sa

int main(int argc, char* argv[])
{
    int sockfd, new_fd;  
    struct addrinfo hints, *server_info, *server_info_ptr;
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1, numbytes=0;
    char s[INET6_ADDRSTRLEN];
    char buf[MAXDATASIZE];
    char *buf_ptr=buf;
    int return_value;

    if (argc != 2)
    {
        cerr << "Usage: ./server port_number\n";
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

    if ((return_value = getaddrinfo(NULL, argv[1], &hints, &server_info)) != 0)
    {
        cerr << "Getting server info: " << gai_strerror(return_value) << endl;
        return EXIT_FAILURE;
    }

    for(server_info_ptr = server_info; server_info_ptr != NULL; server_info_ptr = server_info_ptr->ai_next)
    {
        if ((sockfd = socket(server_info_ptr->ai_family, server_info_ptr->ai_socktype, server_info_ptr->ai_protocol)) == -1)
        {
            perror("Server Process: socket() Error");
            continue;
        }
        
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("Server Process: setsockopt() Error");
            return EXIT_FAILURE;
        }

        if (bind(sockfd, server_info_ptr->ai_addr, server_info_ptr->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("Server Process: bind() Error");
            continue;
        }
        break;
    }
    
    if (server_info_ptr == NULL)
    {
        cerr << "Server Process: bind() failure\n";
        return EXIT_FAILURE;
    }

    freeaddrinfo(server_info); 

    if (listen(sockfd, BACKLOG) == -1) {
        perror("Server Process: listen() Error");
        return EXIT_FAILURE;
    }
    
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("Server Process: sigaction() Error");
        return EXIT_FAILURE;
    }

    printf("Server Process is now running and accepting connections . . .\n");
    
    while(1)
    { 
        sin_size = sizeof client_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        
        if (new_fd == -1)
        {
            perror("Server Process: accept() Error");
            continue;
        }

        inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)&client_addr), s, sizeof s);

        cout << "Server Process: client " << s << " " << argv[1] << " is now connected.\n";

        if (!fork())
        { 
            //close(sockfd); 
            if (send(new_fd, "Hello, client", 14, 0) == -1)
                perror("Server Process: send() Error");

             
            if ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1)
            {
                perror("Server Process: recv() Error");
                return EXIT_FAILURE;
            }

            buf[numbytes] = '\0';
            cout << "Server Process: Received the following message from: " << s << " " << argv[1] << endl << buf << endl;
            

            while (strlen(buf_ptr) > 0)
            {
                for (size_t i=0; i < MAXDATASIZE; ++i)
                    buf[i]='\0';
                if ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1)
                {
                    perror("Server Process: recv() Error");
                    return EXIT_FAILURE;
                }

                buf[numbytes] = '\0';
                cout << buf << endl;
            }

            //close(new_fd);
            //return EXIT_FAILURE;
        }
        
        close(new_fd); 
    }

    return EXIT_SUCCESS;
}


//------------------------------------------------------------------------------
//  MAIN FUNCTION DEFINITIONS
//------------------------------------------------------------------------------

void sigchld_handler(int s)
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void* get_in_addr(struct sockaddr* sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*) sa)->sin_addr);
    
    return &(((struct sockaddr_in6*) sa)->sin6_addr);
}
