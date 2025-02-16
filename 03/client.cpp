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
    std :: cout << "Error socket connection" << std::endl;
}


int main (){

    int fd = socket(AF_INET,SOCK_STREAM,0) ;
    
    if(fd < 0) {
        die("socket");
    }
    
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET ;
    addr.sin_port = ntohs(1234) ;
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);

   // std :: cout << "yes" << std :: endl;
    
    int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if(rv){
        die("connect fail");
    }
    std ::string  msg = "hello";
    write(fd,msg.c_str(),msg.length());
    char buf[1024] = {};
    int size = recv(fd,&buf, sizeof(buf),0); 
    if(size < 0){
        die("read");
    }
    std :: cout << buf << std :: endl;
    close(fd) ;
    
}