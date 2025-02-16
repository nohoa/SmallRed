#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include<iostream>


static void die(std :: string msg ) {
    std :: cout << "Error " << msg  << std::endl;
}

static void do_something(int connfd){
    char msg[1024] = {};
    int size = recv(connfd,&msg, sizeof(msg),0); 
    if(size < 0 ){
        std :: cout << "Error reading from server" << std :: endl ;
        return ;
    }
    std :: cout << msg << std :: endl ;
    
    std :: string write_back = "world" ;
    write(connfd,write_back.c_str(),write_back.length());
}

int main (){
     
    // AF_INET for IPV4 , SOCKET_STREAM for TCP
    int fd = socket(AF_INET, SOCK_STREAM,0) ;

    //std :: cout << "yep" << std :: endl;

    int val = 1 ;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET ;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(0);

    int rv = bind(fd,(const sockaddr *)&addr,sizeof(addr));
    //std :: cout << rv << std :: endl; 
    if(rv){
        die("bind()");
    }

    rv = listen(fd, SOMAXCONN);
    if(rv){
        die("listen()");
    }

    while(true){
       struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        //std :: cout << connfd << std :: endl;
        if(connfd < 0){
            continue ;
        }
        std :: cout << "Client connected" << std :: endl ;
        do_something(connfd);
        close(connfd);
        break;
    }

}